/* game.h
 * Author: Neil Kenney
 * Date: 2/22/25
 * Purpose: store info about game
 * */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <limits>
#include <iomanip>
#include "vector.h"
#include "movie.h"

using namespace std;


class Game {
    public:
    Game(string filename);
    ~Game();
    void playGame();
    void fillInfo();
    void explain();
    void mainQuery(int tgtIndex);
    void listMovies();
    bool handleGuess(int tgtIndex);
    int find(string guess);
    void giveHint(int tgtIndex);

    void compareAll(int gIndex, int tgtIndex);
    void compareYears(int gIndex, int tgtIndex);
    void compareRuntime(int gIndex, int tgtIndex);
    void compareBudget(int gIndex, int tgtIndex);
    void compareEarnings(int gIndex, int tgtIndex);
    void compareScore(int gIndex, int tgtIndex);

    private:
    Vector list;
};

#endif