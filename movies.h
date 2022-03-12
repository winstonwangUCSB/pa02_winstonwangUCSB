
#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>

using namespace std;

class Movie {

 public:
    Movie(string name, double rating);  
    string getName();
    double getRating();
    bool operator<(const Movie& m2);
 private:
	string movieName;
	double movieRating
};

#endif
