#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace TICTACTOE3D
{

int Player::winMatrix[76][4] = 
{
    // Slice 1 Rows
    {0,1,2,3},
    {4,5,6,7},
    {8,9,10,11},
    {12,13,14,15},

    //Slice 1 Columns
    {0,4,8,12},
    {1,5,9,13},
    {2,6,10,14},
    {3,7,11,15},

    // Slice 2 Rows
    {16,17,18,19},
    {20,21,22,23},
    {24,25,26,27},
    {28,29,30,31},

    // Slice 2 Columns
    {16,20,24,28},
    {17,21,25,29},
    {18,22,26,30},
    {19,23,27,31},

    // Slice 3 Rows
    {32,33,34,35},
    {36,37,38,39},
    {40,41,42,43},
    {44,45,46,47},

    // Slice 3 Columns
    {32,36,40,44},
    {33,37,41,45},
    {34,38,42,46},
    {35,39,43,47},

    // Slice 4 Rows
    {48,49,50,51},
    {52,53,54,55},
    {56,57,58,59},
    {60,61,62,63},

    // Slice 4 Columns
    {48,52,56,60},
    {49,53,57,61},
    {50,54,58,62},
    {51,55,59,63},

    // Z Dimension Linear
    {3,19,35,51},
    {7,23,39,55},
    {11,27,43,59},
    {15,31,47,63},
    {0,16,32,48},
    {4,20,36,52},
    {8,24,40,56},
    {12,28,44,60},
    {1,17,33,49},
    {2,18,34,50},
    {13,29,45,61},
    {14,30,46,62},
    {5,21,37,53},
    {6,22,38,54},
    {9,25,41,57},
    {10,26,42,58},

    // Main Diagonals
    {0,21,42,63},
    {12,25,38,51},
    {15,26,37,48},
    {3,22,41,60},

    // Slice Diagonals
    {0,5,10,15},
    {3,6,9,12},
    {16,21,26,31},
    {19,22,25,28},
    {32,37,42,47},
    {35,38,41,44},
    {48,53,58,63},
    {51,54,57,60},

    {0,20,40,60},
    {12,24,36,48},
    {1,21,41,61},
    {13,25,37,49},
    {2,22,42,62},
    {14,26,38,50},
    {3,23,43,63},
    {15,27,39,51},

    {12,29,46,63},
    {15,30,45,60},
    {8,25,42,59},
    {11,26,41,56},
    {4,21,38,55},
    {7,22,37,52},
    {0,17,34,51},
    {3,18,33,48}
};

int Player::rewardBase = 10;

int Player::rewardMatrix[5][5] = 
{
    {0,-10,-100,-1000,-10000},
    {10,0,0,0,0},
    {100,0,0,0,0},
    {1000,0,0,0,0},
    {10000,0,0,0,0},
};

int Player::evaluate(const GameState &pState, int player)
{
    int total = 0;
    
    for(int i = 0; i < 76; i++)
    {
        int x = 0;
        int y = 0;
        for(int j = 0; j < 4; j++)
        {
            if(pState.at(winMatrix[i][j]) == CELL_X)
            {
                x++;
            }
            else if(pState.at(winMatrix[i][j]) == CELL_O)
            {
                y++;
            }
        }

        total += rewardMatrix[x][y];
    }

    return total;

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
    else if(player == CELL_X)
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
        int v = minimaxalphabeta(lNextStates[i],0,INT_MIN,INT_MAX,lNextStates[i].getNextPlayer());
        if(v > largest_v)
        {
            largest_v = v;
            index = i;
        }
    }

    return lNextStates[index];
}

/*namespace TICTACTOE3D*/ }
