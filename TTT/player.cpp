#include "player.hpp"
#include <cstdlib>

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
int minimax(const GameState &pState)
{
    std::cout << "Call of method minimax\n";

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    int maxIndex = -1;
    int maxValue = -1000;
    for(int i = 0; i < lNextStates.size(); i++)
    {
        int value = minimax(lNextStates[i]);
        if(value > maxValue){
            value = maxValue;
            maxIndex = i;
        }
    }

    return maxIndex;
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);



    // we are already in a terminal state
    // so we cannot do anything else than
    // returning what we got

    if (lNextStates.size() == 0) return GameState(pState, Move());

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
