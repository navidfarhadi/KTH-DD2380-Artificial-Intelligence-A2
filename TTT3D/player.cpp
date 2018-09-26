#include "player.hpp"
#include <cstdlib>

namespace TICTACTOE3D
{

int Player::evaluate(const GameState &pState, int player)
{
    return 0;   
}

int Player::alphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{

    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);
    int v;
    
    if(depth == 0 || nextStates.size() == 0)
    {
        v = evaluate(pState, player);
    }
    else if(player == CELL_X){
        v = -(1 << 14);
        for(GameState state : nextStates){
            v = std::max(v, alphabeta(state, (depth - 1), alpha, beta, CELL_O));
            alpha = std::max(alpha, v);
            if(beta <= alpha){
                break;
            }
        }
    }
    else{
        v = 1 << 14;
        for(GameState state : nextStates){
            v = std::min(v, alphabeta(state, (depth - 1), alpha, beta, CELL_X));
            beta = std::min(beta, v);
            if(beta <= alpha){
                break;
            }
        }
    }

    return v;

}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    
    if (lNextStates.size() == 0) return GameState(pState, Move());

    int maxValue = - (1 << 14);
    int maxIndex = 0;

    for(int i = 0; i < lNextStates.size(); i++){
        std::cerr << "Processing state: " << i << "\n";
        int v = alphabeta(lNextStates[i],2,-1000,1000, pState.getNextPlayer());
        if(v > maxValue){
            maxValue = v;
            maxIndex = i;
        }
    }

    return lNextStates[maxIndex];

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }
