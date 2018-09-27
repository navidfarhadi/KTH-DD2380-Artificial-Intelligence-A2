#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace TICTACTOE
{

int Player::gamma(const GameState &pState)
{
    int v = 0;

    if(pState.getNextPlayer() == CELL_X)
    {
        if(pState.isXWin())
        {
            v = 1;
        }
        else
        {
            v = 0;
        }
    }
    else
    {
        if(pState.isOWin())
        {
            v = -1;
        }
        else
        {
            v = 0;
        }
    }

    return v;
}

int Player::minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{
    int v;

    if(depth == 0 || pState.isEOG())
    {
        v = gamma(pState);
    }

    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(player == CELL_X)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            v = std::max(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_O));
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
            v = std::min(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_X));
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
    int index;

    for(int i = 0; i < lNextStates.size(); i++)
    {
        int v = minimaxalphabeta(lNextStates[i],3,INT_MIN,INT_MAX,lNextStates[i].getNextPlayer());
        if(v > largest_v)
        {
            largest_v = v;
            index = i;
        }
    }

    return lNextStates[index];
}

/*namespace TICTACTOE*/ }
