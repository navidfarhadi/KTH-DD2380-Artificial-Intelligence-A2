#ifndef _CHECKERS_PLAYER_HPP_
#define _CHECKERS_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace checkers
{

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    int minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player);
    int evaluate(const GameState &pState, int player);
    GameState play(const GameState &pState, const Deadline &pDue);
    int minimaxalphabeta(const GameState &pState, int depth, int alpha, int beta, int player);
    int evaluate(const GameState &pState, int player);
    static int color;
};

/*namespace checkers*/ }

#endif
