#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace TICTACTOE3D
{

int Player::evaluate(const GameState &pState, int player){
    if(pState.isOWin()){
        return 100000;
    }
    else if(pState.isXWin()){
        return -10000;
    }
    else{
        return 0;
    }
}

int Player::minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{
    int v;

    if(depth <= 0 || pState.isEOG())
    {
        v = evaluate(pState,player);
    }

    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(player == CELL_X)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            v = std::max (v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_O));
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
            v = std::min(v, minimaxalphabeta(child,depth-1,alpha,beta,CELL_X));
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
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());

    int largest_v = INT_MIN;
    int index = -1;

    for(int i = 0; i < lNextStates.size(); i++)
    {
        int v = minimaxalphabeta(lNextStates[i],1,INT_MIN,INT_MAX,lNextStates[i].getNextPlayer());
        if(v > largest_v)
        {
            largest_v = v;
            index = i;
        }
    }

    return lNextStates[index];
}

/*namespace TICTACTOE3D*/ }
