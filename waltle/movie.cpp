/* movie.cpp
 * Author: Neil Kenney
 * Date: 2/22/25
 * Purpose: set, get, and delete information about characters
 * */

#include "movie.h"

Movie::Movie(string title, int year, int runtime, float budget, 
             float earnings, float score, string locHint, string prodHint, 
             string plotHint) {
    this->title = title;
    this->year = year;
    this->runtime = runtime;
    this->budget = budget;
    this->earnings = earnings;
    this->score = score;
    this->locHint = locHint;
    this->prodHint = prodHint;
    this->plotHint = plotHint;
}

Movie::~Movie() {
}

string Movie::getName() {
    return title;
}

int Movie::getYear() {
    return year;
}

int Movie::getRuntime() {
    return runtime;
}

float Movie::getBudget() {
    return budget;
}

float Movie::getEarnings() {
    return earnings;
}

float Movie::getScore() {
    return score;
}

string Movie::getLocHint() {
    return locHint;
}

string Movie::getProdHint() {
    return prodHint;
}

string Movie::getPlotHint() {
    return plotHint;
}