#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace checkers
{

class FastExit {};

static int evaluate(const GameState &pState, int player)
{
    int score = 0;
    
    if(pState.isEOG()) {
        if(pState.isDraw()) return -5000;
        if(pState.isWhiteWin() && player == CELL_WHITE) return 10000;
        if(pState.isWhiteWin() && player == CELL_RED) return -10000;
        if(pState.isRedWin() && player == CELL_WHITE) return -10000;
        if(pState.isRedWin() && player == CELL_RED) return 10000;
    }
    
    for (int i = 0; i < 32; i++) {
        uint8_t cell = pState.at(i);
        int val = -1;
        
        if(cell == CELL_EMPTY) val = 0;
        if(cell & CELL_INVALID) val = 0;
        if(cell & player) val *= -1;
        if(cell & CELL_KING) val *= 3;
        
        score += val;
    }

    //close to get a king
    for(int i = 0; i < 32; i++){
        uint8_t cell = pState.at(i);
        // this does not hold us back
        if(cell & CELL_KING) break;

        if(cell & CELL_RED && pState.cellToRow(i) == 6){
            if(player == CELL_RED){
                score += 2;
            }
            else{
                score -= 2;
            }
        }
        else if(cell & CELL_WHITE && pState.cellToRow(i) == 1){
            if(player == CELL_WHITE){
                score += 2;
            }
            else{
                score -= 2;
            }
        }
    }
    
    return score;
}

static std::pair<int, bool> minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player, bool maximizingPlayer, const Deadline &pDue)
{
    if(pDue - Deadline::now() < 0.02) throw FastExit();
    
    int v;
    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(depth == 0 || pState.isEOG())
    {
        return {evaluate(pState, player), !pState.isEOG()};
    }
    
    bool remainingChildren = false;
    if(maximizingPlayer)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            auto res = minimaxalphabeta(child,depth-1,alpha,beta,player, false, pDue);
            if(res.second) remainingChildren = true;
            v = std::max(v, res.first);
            alpha = std::max(alpha,v);
            if(beta <= alpha)
            {
                break;
            }
        }
    }
    else
    {
        v = INT_MAX;
        for(GameState child : nextStates)
        {
            auto res = minimaxalphabeta(child,depth-1,alpha,beta,player, true, pDue);
            if(res.second) remainingChildren = true;
            v = std::min(v, res.first);
            beta = std::min(beta,v);
            if(beta <= alpha)
            {
                break;
            }
        }
    }

    return {v, remainingChildren};
}


GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());
    

    int depth = 5;
    int index = 0;
    int largest_v = 0;
    
    while(true) {
        
        Deadline start(Deadline::now());
    
        int largest_v_loop = INT_MIN;
        int index_loop = -1;
        bool remainingChildren = false;

        try {
            for(long unsigned int i = 0; i < lNextStates.size(); i++)
            {
                auto res = minimaxalphabeta(lNextStates[i],depth,INT_MIN,INT_MAX,pState.getNextPlayer(), false, pDue);
                int v = res.first;
                if(res.second) remainingChildren = true;
                if(v > largest_v_loop)
                {
                    largest_v_loop = v;
                    index_loop = i;
                }
            }
        
            depth++;
            
            largest_v = largest_v_loop;
            index = index_loop;
            
            if(!remainingChildren) break;

            if(largest_v == 10000){
                // we found what we needed to find
                break;
            }
            
            //double searchtime = Deadline::now() - start;
            //double lefttime = pDue - Deadline::now();
            
            //std::cerr << "Depth " << depth << ", search " << searchtime << ", left " << lefttime << std::endl;
            //if(lefttime < searchtime * 1.5) break;
        } catch(const FastExit &) {
            //std::cerr << "Depth " << depth + 1 << " fast exit" << std::endl;
            break;
        }
    }

    std::cerr << "Picking move with value " << largest_v << " using depth " << depth << std::endl;
    
    return lNextStates[index];
}

/*namespace checkers*/ }
