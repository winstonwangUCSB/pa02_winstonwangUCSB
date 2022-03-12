
#include "movies.h"

#include <iostream>
using namespace std;


Movie::Movie(string name, double rating) {
	movieName = name;
	movieRating = rating;
}

string Movie::getName() const {
	return movieName;
}
double Movie::getRating() const {
	return movieRating;
}

bool Movie::operator<(const Movie& m2) {
	return getName().compare(m2.getName()) < 0;
}

