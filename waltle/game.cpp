/* game.cpp
 * Author: Neil Kenney
 * Date: 2/22/25
 * Purpose: run one round of Waltdle game
 * */

#include "game.h"

Game::Game(string filename) {    
    ifstream infile;
    infile.open(filename);
    if (infile.fail()) {
        cout << "Error occurred while opening file" << endl;
        exit(EXIT_FAILURE); 
    }
    string mTitle, hint1, hint2, hint3;
    int mYear, mRuntime;
    float mBudget, mEarnings, mScore;
    Data add;
    for (int i = 0; i < 20; i++) {
        getline(infile, mTitle);
        getline(infile, hint1);
        getline(infile, hint2);
        getline(infile, hint3);
        infile >> mYear;
        infile >> mRuntime;
        infile >> mBudget;
        infile >> mEarnings;
        infile >> mScore;
        add = new Movie(mTitle, mYear, mRuntime, mBudget, mEarnings, mScore,
                        hint1, hint2, hint3);
        this->list.push_back(add);
        infile.ignore();
    }
    infile.close();
}

void Game::playGame() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, NUM_MOVIES-1);
    int rdIndex = dis(gen);
    explain();
    mainQuery(rdIndex);
}

Game::~Game() {
    int storeSize = list.size();
    for (int i=0; i<storeSize; i++) {
        delete list.at(i);
    }
}

void Game::explain() {
    cout << endl << "\033[94m";
    cout << "Welcome to \033[1mWaltle\033[0m\033[94m, the Walt Disney guessing";
    cout << " game! The goal of the" << endl;
    cout << "game is to track down a mystery animated movie produced by Walt";
    cout << endl;
    cout << "during his lifetime. You have 5 guesses in total. After each";
    cout << endl;
    cout << "incorrect answer, you will be provided information about your";
    cout << endl;
    cout << "guessed film and how it compares to the correct one. At any point";
    cout << endl;
    cout << "in the game, you may view a list of all movies or receive a hint.";
    cout << endl;
    cout << "To get started, enter the number corresponding to your desired ";
    cout << endl;
    cout << "request.\033[0m" << endl << endl;
}

void Game::mainQuery(int tgtIndex) {
    int round = 1;
    cout << "1: make a guess" << endl << "2: list movies" << endl; 
    cout << "3: get a hint" << endl << "4: see stats" << endl << "5: quit game";
    cout << endl << endl;
    cout << "\033[4mEnter a number 1-5\033[0m: ";
    int choice;
    cin >> choice;
    while (choice != 5) {
        if (choice == 1) {
            bool isWinner = handleGuess(tgtIndex);
            if (isWinner) {
                break;
            }
            round++;
        }
        if (round > 5) {
            cout << "\033[31mYou lost. Better luck next time!\033[0m" << endl;
            cout << endl << "The correct answer was..." << endl << endl;
            cout << "Title: " << this->list.at(tgtIndex)->getName();
            displayStats(tgtIndex);
            break;
        }
        if (round == 5) {
            cout << "\033[38;5;202mYou have one guess remaining. ";
            cout << "Use it wisely...\033[0m" << endl << endl;
        }
        if (choice == 2) {
            listMovies();
        }
        if (choice == 3) {
            giveHint(tgtIndex);
        }
        if (choice == 4) {
            displayStats(tgtIndex);
            cout << endl;
        }
        cout << "1: make a guess" << endl << "2: list movies" << endl; 
        cout << "3: get a hint" << endl << "4: see stats" << endl;
        cout << "5: quit game" << endl << endl;
        cout << "\033[4mEnter a number 1-5\033[0m: ";
        cin >> choice;
    }
    cout << endl << "\033[94m";
    cout << "Thanks for playing Waltle! Have a magical rest of your day!";
    cout << endl << endl << "\033[0m";
    char keepPlaying;
    cout << "Would you like to play another round? (y/n) ";
    cin >> keepPlaying;
    if (keepPlaying == 'y') {
        playGame();
    }
}

void Game::listMovies() {
    cout << endl;
    for (int i = 0; i < NUM_MOVIES; i++) {
        cout << this->list.at(i)->getName() << endl;
    }
    cout << endl;
}

bool Game::handleGuess(int tgtIndex) {
    cout << endl << "\033[4mEnter a movie title\033[0m: ";
    string guess;
    cin.ignore();
    getline(cin, guess);
    int gIndex = find(guess);
    if (gIndex == NUM_MOVIES) {
        cout << endl;
        cout << "Inputted title is not in list. Please check spelling. ";
        cout << "If needed, check list by typing \"2\"" << endl << endl;
        return false;
    }
    if (gIndex == tgtIndex) {
        cout << endl << "\033[32mYou won!\033[0m" << endl;
        winnerStats(tgtIndex);
        return true;
    }
    compareAll(gIndex, tgtIndex);
    return false;
}

int Game::find(string guess) {
    for (int i = 0; i < NUM_MOVIES; i++) { 
        if (this->list.at(i)->getName() == guess) {
            return i;
        }
    }
    return NUM_MOVIES;
}

void Game::giveHint(int tgtIndex) {
    cout << endl << "Would you like a hint about:" << endl;
    cout << "1: Setting" << endl;
    cout << "2: Production" << endl;
    cout << "3: Plot" << endl << endl;
    cout << "\033[4mEnter a number 1-3\033[0m: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << endl << "\033[94m";
        cout << this->list.at(tgtIndex)->getLocHint() << "\033[0m";
        cout << endl << endl;
    }
    if (choice == 2) {
        cout << endl << "\033[94m";
        cout << this->list.at(tgtIndex)->getProdHint() << "\033[0m";
        cout << endl << endl;
    }
    else if (choice == 3) {
        cout << endl << "\033[94m";
        cout << this->list.at(tgtIndex)->getPlotHint() << "\033[0m";
        cout << endl << endl;
    }
}

void Game::compareAll(int gIndex, int tgtIndex) {
    cout << endl;
    compareYears(gIndex, tgtIndex);
    compareRuntime(gIndex, tgtIndex);
    compareBudget(gIndex, tgtIndex);
    compareEarnings(gIndex, tgtIndex);
    compareScore(gIndex, tgtIndex);
    cout << endl;
}

void Game::compareYears(int gIndex, int tgtIndex) {
    cout << "Release year: " << this->list.at(gIndex)->getYear();
    int guessYear = this->list.at(gIndex)->getYear();
    int answerYear = this->list.at(tgtIndex)->getYear();
    if (guessYear > answerYear) {
        cout << " \033[31m(too recent)\033[0m" << endl;
    }
    else if (guessYear < answerYear) {
        cout << " \033[31m(too old)\033[0m" << endl;
    }
    else {
        cout << " \033[32m(correct)\033[0m" << endl;
    }
}

void Game::compareRuntime(int gIndex, int tgtIndex) {
    cout << "Runtime: " << this->list.at(gIndex)->getRuntime();
    int guessRuntime = this->list.at(gIndex)->getRuntime();
    int answerRuntime = this->list.at(tgtIndex)->getRuntime();
    if (guessRuntime > answerRuntime) {
        cout << " \033[31m(too long)\033[0m" << endl;
    }
    else if (guessRuntime < answerRuntime) {
        cout << " \033[31m(too short)\033[0m" << endl;
    }
    else {
        cout << " \033[32m(correct)\033[0m" << endl;
    }
}

void Game::compareBudget(int gIndex, int tgtIndex) {
    float guessBudget = this->list.at(gIndex)->getBudget();
    float answerBudget = this->list.at(tgtIndex)->getBudget();
    if (guessBudget == 0) {
        cout << "No budget data";
    }
    else {
        cout << "Budget (millions of $): " << guessBudget;
    }
    if (answerBudget == 0) {
        cout << " \033[38;5;202m(unable to compare budgets)\033[0m" << endl;
    }
    else if (guessBudget > answerBudget) {
        cout << " \033[31m(too expensive)\033[0m" << endl;
    }
    else if (guessBudget < answerBudget) {
        cout << " \033[31m(too cheap)\033[0m" << endl;
    }
    else {
        cout << " \033[32m(correct)\033[0m" << endl;
    }
}

void Game::compareEarnings(int gIndex, int tgtIndex) {
    float guessEarnings = this->list.at(gIndex)->getRuntime();
    float answerEarnings = this->list.at(tgtIndex)->getEarnings();
    cout << "Earnings (millions of $): " << guessEarnings;
    if (guessEarnings > answerEarnings) {
        cout << " \033[31m(too much)\033[0m" << endl;
    }
    else if (guessEarnings < answerEarnings) {
        cout << " \033[31m(not enough)\033[0m" << endl;
    }
    else {
        cout << " \033[32m(correct)\033[0m" << endl;
    }
}

void Game::compareScore(int gIndex, int tgtIndex) {
    float guessScore = this->list.at(gIndex)->getScore();
    float answerScore = this->list.at(tgtIndex)->getScore();
    cout << "IMDb score (out of 10.0): " << guessScore;
    if (guessScore > answerScore) {
        cout << " \033[31m(too good)\033[0m" << endl;
    }
    else if (guessScore < answerScore) {
        cout << " \033[31m(too bad)\033[0m" << endl;
    }
    else {
        cout << " \033[32m(correct)\033[0m" << endl;
    }
}

void Game::winnerStats(int tgtIndex) {
    cout << endl;
    cout << "Title: " << this->list.at(tgtIndex)->getName();
    cout << " \033[32m(correct)\033[0m" << endl;
    cout << "Release year: " << this->list.at(tgtIndex)->getYear();
    cout << " \033[32m(correct)\033[0m" << endl;
    cout << "Runtime: " << this->list.at(tgtIndex)->getRuntime();
    cout << " \033[32m(correct)\033[0m" << endl;
    float answerBudget = this->list.at(tgtIndex)->getBudget();
    if (answerBudget == 0) {
        cout << "No budget data";
    }
    else {
        cout << "Budget (millions of $): " << answerBudget;
        cout << " \033[32m(correct)\033[0m";
    }
    cout << endl;
    cout << "Earnings (millions of $): ";
    cout << this->list.at(tgtIndex)->getEarnings();
    cout << " \033[32m(correct)\033[0m" << endl;
    cout << "IMDb score (out of 10.0): " << this->list.at(tgtIndex)->getScore();
    cout << " \033[32m(correct)\033[0m" << endl;
}

void Game::displayStats(int tgtIndex) {
    cout << endl;
    cout << "Release year: " << this->list.at(tgtIndex)->getYear();
    cout << endl;
    cout << "Runtime: " << this->list.at(tgtIndex)->getRuntime();
    cout << endl;
    float answerBudget = this->list.at(tgtIndex)->getBudget();
    if (answerBudget == 0) {
        cout << "No budget data";
    }
    else {
        cout << "Budget (millions of $): " << answerBudget;
    }
    cout << endl;
    cout << "Earnings (millions of $): ";
    cout << this->list.at(tgtIndex)->getEarnings();
    cout << endl;
    cout << "IMDb score (out of 10.0): " << this->list.at(tgtIndex)->getScore();
    cout << endl;
}