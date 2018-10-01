#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace checkers
{

int Player::evaluate(const GameState &pState, int player){
    int count_red = 0;
    int count_white = 0;
    for(int i = 0; i < 32; i++){
        if(pState.at(i) == CELL_RED) count_red++;
        if(pState.at(i) == CELL_WHITE) count_white++;
    }
    return (count_red - count_white);
}

int Player::minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{
    int v;
    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(depth == 0 || pState.isEOG())
    {
        v = evaluate(pState, player);
    }
    else if(player == CELL_INVALID)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            v = std::max(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_INVALID));
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
            v = std::min(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_INVALID));
            beta = std::min(beta,v);
            if(beta <= alpha)
            {
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
    

    int largest_v = INT_MIN;
    int index = -1;

    for(long unsigned int i = 0; i < lNextStates.size(); i++)
    {
        int v = minimaxalphabeta(lNextStates[i],6,INT_MIN,INT_MAX,lNextStates[i].getNextPlayer());
        if(v > largest_v)
        {
            largest_v = v;
            index = i;
        }
    }

    return lNextStates[index];
}

/*namespace checkers*/ }
