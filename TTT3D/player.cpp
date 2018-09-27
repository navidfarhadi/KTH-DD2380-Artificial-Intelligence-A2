#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <climits>

namespace TICTACTOE3D
{

// all tested
int check_rows(const GameState &pState)
{
    int ret = 0;
    int player = pState.getNextPlayer();
    for(int i = 0; i < 16; i++){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i*4 + j)&player > 0){
                count++;
            }
            //std::cerr << (i*4 + j) << " ";
        }
        //std::cerr << "\n";
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else                                    return ret;
}

int check_cols(const GameState &pState){
    int ret = 0;
    int player = pState.getNextPlayer();
    for(int k = 0; k < 4; k++){
        for(int i = 0; i < 4; i++){
            int count = 0;
            for(int j = 0; j < 4; j++){
                if(pState.at(i + j * 4 + k*16)&player > 0){
                    count++;
                }
                //std::cerr << (i + j * 4 + k*16) << " ";
            }
            //std::cerr << "\n";
        }
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else return ret;
}

int check_lines(const GameState &pState)
{
    int ret = 0;
    int player = pState.getNextPlayer();
    for(int i = 0; i < 16; i++){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i + j * 16)&player > 0){
                count++;
            }
            //std::cerr << (i + j * 16) << " ";
        }
        //std::cerr << "\n";
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else return ret;
}

int check_x_diags(const GameState &pState){
    int ret = 0;
    int player = pState.getNextPlayer();
    // up left to down right
    for(int i = 0; i < 64; i = i + 16){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i + j * 5)&player > 0){
                count++;
            }
            //std::cerr << (i + j * 5) << " ";
        }
        //std::cerr << "\n";
    }
    for(int i = 0; i < 64; i = i + 16){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(12 + i - j * 3)&player > 0){
                count++;
            }
            //std::cerr << (12 + i - j * 3) << " ";
        }
        //std::cerr << "\n";
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else return ret;
}

int check_y_diags(const GameState &pState){
    int ret = 0;
    int player = pState.getNextPlayer();
    // up left to down right
    for(int i = 0; i < 4; i++){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i + j * 20)&player > 0){
                count++;
            }
            //std::cerr << (i + j * 20) << " ";
        }
        //std::cerr << "\n";
    }
    for(int i = 48; i < 52; i++){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i - j * 12)&player > 0){
                count++;
            }
            //std::cerr << (i - j * 12) << " ";
        }
        //std::cerr << "\n";
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else return ret;
}

int check_z_diags(const GameState &pState){
    int ret = 0;
    int player = pState.getNextPlayer();
    // up left to down right
    for(int i = 0; i < 16; i = i + 4){
        int count = 0;
        for(int j = 0; j < 4; j++){
            if(pState.at(i + j * 17)&player > 0){
                count++;
            }
            std::cerr << (i + j * 17) << " ";
        }
        std::cerr << "\n";
    }
    for(int i = 3; i < 16; i = i + 4){
        int count = 0;
        for(int j = 0; j < 4; j++){
            /*if(pState.at(i + j * 9)&player > 0){
                count++;
            }*/
            std::cerr << (i + j * 15) << " ";
        }
        std::cerr << "\n";
    }
    ret *= 10;
    if(player == CELL_X)    return -ret;
    else return ret;
}

int check_main_diag(const GameState &pState)
{   
    int offset = 0;
    for(int i = 0; i < 4; i++){
        std::cerr << (offset + i*21) << " ";
    }
    std::cerr << "\n";

    offset = 12;
    for(int i = 0; i < 4; i++){
        std::cerr << (offset + i*13) << " ";
    }
    std::cerr << "\n";

    offset = 3;
    for(int i = 0; i < 4; i++){
        std::cerr << (offset + i*19) << " ";
    }
    std::cerr << "\n";

    offset = 15;
    for(int i = 0; i < 4; i++){
        std::cerr << (offset + i*11) << " ";
    }
    std::cerr << "\n";
    return 0;
}

int Player::evaluate(const GameState &pState){
    if(pState.isOWin()){
        return 100000;
    }
    else if(pState.isXWin()){
        return -10000;
    }
    else{
        int ret = 0;
        ret =  check_main_diag(pState) ;//+ check_rows(pState) + check_depth(pState);
        return ret;
    }
}

int Player::gamma(const GameState &pState)
{
    int v = 0;

    evaluate(pState);

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
    std::vector<GameState> nextStates;
    pState.findPossibleMoves(nextStates);

    if(depth == 0 || pState.isEOG())
    {
        v = gamma(pState);
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
