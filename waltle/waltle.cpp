/* waltle.cpp
 * Author: Neil Kenney
 * Date: 2/22/25
 * Purpose: administrate game
 * */

#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Error: not enough arguments provided on command line." << endl;
        exit(EXIT_FAILURE);
    }
    Game alpha(argv[1]);
    alpha.playGame();
    return 0;
}