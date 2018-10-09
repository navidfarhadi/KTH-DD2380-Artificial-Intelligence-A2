#include "player.hpp"
#include <cstdlib>
#include <climits>

namespace checkers
{

int Player::evaluate(const GameState &pState, int player)
{
    int total = 0;
    int redTotal = 0;
    int whiteTotal = 0;

    if(!pState.isEOG())
    {
        for(int i = 0; i < pState.cSquares; i++)
        {
            if(pState.at(i) == CELL_WHITE)
            {
                whiteTotal += 20;

                if(player == CELL_WHITE)
                {
                    if(pState.cellToCol(i) == 0)
                    {
                        total += 10;
                    }
                    else if(pState.cellToRow(i) == 0)
                    {
                        total += 10;
                    }
                    else if(pState.cellToCol(i) == 1)
                    {
                        total += 5;
                    }
                    else if(pState.cellToCol(i) == 6)
                    {
                        total += 5;
                    }
                    else if(pState.cellToCol(i) == 7)
                    {
                        total += 10;
                    }
                    else if(pState.cellToRow(i) == 7)
                    {
                        total += 10;
                    }
                }
                else if(player == CELL_RED)
                {
                    if(pState.cellToCol(i) == 0)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToRow(i) == 0)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToCol(i) == 1)
                    {
                        total -= 5;
                    }
                    else if(pState.cellToCol(i) == 6)
                    {
                        total -= 5;
                    }
                    else if(pState.cellToCol(i) == 7)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToRow(i) == 7)
                    {
                        total -= 10;
                    }
                }

                if(pState.at(i) == CELL_KING)
                {
                    whiteTotal += 150;
                }
                else
                {
                    if(player == CELL_WHITE)
                    {
                        if(pState.cellToRow(i) == 1)
                        {
                            total += 5;
                        }
                        else if(pState.cellToRow(i) == 2)
                        {
                            total += 5;
                        }
                    }
                    else if(player == CELL_RED)
                    {
                        if(pState.cellToRow(i) == 1)
                        {
                            total -= 5;
                        }
                        else if(pState.cellToRow(i) == 2)
                        {
                            total -= 5;
                        }
                    }
                }
            }
            else if(pState.at(i) == CELL_RED)
            {
                redTotal += 20;

                if(player == CELL_RED)
                {
                    if(pState.cellToCol(i) == 0)
                    {
                        total += 10;
                    }
                    else if(pState.cellToRow(i) == 0)
                    {
                        total += 10;
                    }
                    else if(pState.cellToCol(i) == 1)
                    {
                        total += 5;
                    }
                    else if(pState.cellToCol(i) == 6)
                    {
                        total += 5;
                    }
                    else if(pState.cellToCol(i) == 7)
                    {
                        total += 10;
                    }
                    else if(pState.cellToRow(i) == 7)
                    {
                        total += 10;
                    }
                }
                else if(player == CELL_WHITE)
                {
                    if(pState.cellToCol(i) == 0)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToRow(i) == 0)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToCol(i) == 1)
                    {
                        total -= 5;
                    }
                    else if(pState.cellToCol(i) == 6)
                    {
                        total -= 5;
                    }
                    else if(pState.cellToCol(i) == 7)
                    {
                        total -= 10;
                    }
                    else if(pState.cellToRow(i) == 7)
                    {
                        total -= 10;
                    }
                }

                if(pState.at(i) == CELL_KING)
                {
                    redTotal += 150;
                }
                else
                {
                    if(player == CELL_RED)
                    {
                        if(pState.cellToRow(i) == 6)
                        {
                            total += 5;
                        }
                        else if(pState.cellToRow(i) == 5)
                        {
                            total += 5;
                        }
                    }
                    else if(player == CELL_WHITE)
                    {
                        if(pState.cellToRow(i) == 6)
                        {
                            total -= 5;
                        }
                        else if(pState.cellToRow(i) == 5)
                        {
                            total -= 5;
                        }
                    }
                }
            }
        }

        if(player == CELL_RED)
        {
            return total + redTotal - whiteTotal;
        }
        else
        {
            return total + whiteTotal - redTotal;
        }
    }
    else
    {
        if(player == CELL_RED && pState.isRedWin())
        {
            return 5000;
        }
        else if (player == CELL_WHITE && pState.isWhiteWin())
        {
            return 5000;
        }
        else if (player == CELL_RED && pState.isWhiteWin())
        {
            return -5000;
        }
        else if (player == CELL_WHITE && pState.isRedWin())
        {
            return -5000;
        }
        else
        {
            return 0;
        }
    }
}

int Player::minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player)
{
    int v;
    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(depth == 0 || pState.isEOG())
    {
        v = evaluate(pState, color);

        if(v > 500) return v;
    }
    else if(player == CELL_RED)
    {
        v = INT_MIN;
        for(GameState child : nextStates)
        {
            v = std::max(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_WHITE));
            alpha = std::max(alpha,v);
            if(beta <= alpha)
            {
                break;
            }
        }
    }
    else if(player == CELL_WHITE)
    {
        v = INT_MAX;
        for(GameState child : nextStates)
        {
            v = std::min(v,minimaxalphabeta(child,depth-1,alpha,beta,CELL_RED));
            beta = std::min(beta,v);
            if(beta <= alpha)
            {
                break;
            }
        }
    }

    return v;
}

int Player::color;

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
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
