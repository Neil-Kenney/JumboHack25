/* movie.h
 * Author: Neil Kenney
 * Date: 2/22/25
 * Purpose: declare Princess struct and hold information about characters
 * */

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

using namespace std;

const int NUM_MOVIES = 20;

class Movie {
    public:
    Movie(string title, int year, int runtime, float budget, float earnings,
          float score, string locHint, string prodHint, string plotHint);
    ~Movie();
    string getName();
    int getYear();
    int getRuntime();
    float getBudget();
    float getEarnings();
    float getScore();
    string getLocHint();
    string getProdHint();
    string getPlotHint();

    private:
    string title, locHint, prodHint, plotHint;
    int year, runtime;
    float budget, earnings, score;
};

#endif