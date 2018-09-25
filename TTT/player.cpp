#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace TICTACTOE
{

/**
 * evaluates a certain state
 * returns a value that says how
 * good a state is for a player
 */
int evaluate(const GameState &pState)
{
    return -1;
}
/**
 * implementation of the alpa-beta
 * pruning algorithm adapted to the
 * 2D TIC-TAC-TOE game
 */
// int minimax(const GameState &pState)
// {
//     std::cout << "Call of method minimax\n";

//     std::vector<GameState> lNextStates;
//     pState.findPossibleMoves(lNextStates);

//     int maxIndex = -1;
//     int maxValue = -1000;
//     for(int i = 0; i < lNextStates.size(); i++)
//     {
//         int value = minimax(lNextStates[i]);
//         if(value > maxValue){
//             value = maxValue;
//             maxIndex = i;
//         }
//     }

//     return maxIndex;
// }

int Player::minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{
    if(depth == 0 && pState.isEOG())
    {
        if(pState.getNextPlayer() == CELL_X)
        {
            if(pState.isXWin())
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if(pState.isOWin())
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
    }

    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);
    int v;

    if(player == CELL_X)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            v = minimaxalphabeta(child,depth-1,alpha,beta,CELL_O);
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
            v = minimaxalphabeta(child,depth-1,alpha,beta,CELL_X);
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
