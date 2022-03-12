// Winter'22
// Instructor: Diba Mirza
// Student name: Winston Wang 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include "movies.h"
using namespace std;

class ratingCompare {
	public :
	bool operator() (Movie m1, Movie m2) const {
		if (m1.getRating() == m2.getRating()) {
			return m1.getName() > m2.getName();
		}
		return m1.getRating() <= m2.getRating();
	}
};

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
  if(argc < 2){
    cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
    cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
    exit(1);
  }


  ifstream movieFile (argv[1]);
 

  if (movieFile.fail()){
    cerr << "Could not open file " << argv[1];
    exit(1);
  }
  
//Create an object of a STL data-structure to store all the movies
vector<Movie> movieVect;

string line, movieName;
double movieRating;
// Read each file and store the name and rating
while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
  parseLine(line, movieName, movieRating);
  Movie m = Movie(movieName, movieRating);
  movieVect.push_back(m);
  // Use std::string movieName and double movieRating
  // to construct your Movie objects
  // cout << movieName << " has rating " << movieRating << endl;
  // insert elements into your data structure
}

movieFile.close();

if(argc == 2){
  //print all the movies in ascending alphabetical order of movie names
  sort(movieVect.begin(), movieVect.end());
  while(!movieVect.empty()) {
    cout <<  movieVect.at(0).getName() << ", " << std::fixed << std::setprecision(1) << movieVect.at(0).getRating() << endl;
    movieVect.erase(movieVect.begin());
  } 
  return 0;
}
priority_queue<Movie,vector<Movie>, ratingCompare> prefixMovies;
vector<string> prefixes;
string currStr;
bool multipleWords = false;
for (int i = 2; i < argc; i++) {
	string str = argv[i];
	if (multipleWords) {
		currStr += str;
		if (str.back() == '"') {	
			currStr.pop_back();
			prefixes.push_back(currStr);
			multipleWords = false;
			currStr = "";	
		}
	}
	if (str.front() == '"') {
		multipleWords = true;
		currStr += str.substr(1);
	} else {
		prefixes.push_back(str);
	}
}
//  For each prefix,
//  Find all movies that have that prefix and store them in an appropriate data structure
//  If no movie with that prefix exists print the following message
vector<Movie> highRating;

for (int i = 0; i < prefixes.size(); i++) {
	for (int j = 0; j < movieVect.size(); j++) {
		if (movieVect.at(j).getName().rfind(prefixes.at(i), 0) == 0) {
			prefixMovies.push(movieVect.at(j));
		}
	}	
	if (prefixMovies.empty()) {
                highRating.push_back(Movie("", 0.0));
        } else {
                highRating.push_back(prefixMovies.top());
        }
	if (prefixMovies.empty()) {
		cout<<"No movies found with prefix "<< prefixes.at(i) <<endl;
	} else {
		while (!prefixMovies.empty()) {
			Movie mPop = prefixMovies.top();
			cout << mPop.getName() << ", " << std::fixed << std::setprecision(1) << mPop.getRating() << endl;
			prefixMovies.pop();
		}
	}
	cout << endl;
} 


//  For each prefix,
//  Print the highest rated movie with that prefix if it exists.
//
for (int i = 0; i < prefixes.size(); i++) {
	if (highRating.at(i).getName().compare("") != 0) {
cout << "Best movie with prefix "<<prefixes.at(i)<<" is: " << highRating.at(i).getName() <<" with rating " << std::fixed << std::setprecision(1) << highRating.at(i).getRating() << endl;
	}
}
return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/



bool parseLine(string &line, string &movieName, double &movieRating) {
  if(line.length() <= 0) return false;
  string tempRating = "";

  bool flag = false;
  movieName = tempRating = "", movieRating = 0.0, flag = false;

  for (int i = 0; i < line.length(); i++){
    if(flag) tempRating += line[i];
    else if(line[i]==','&& line[0]!='"') flag = true;
    else {
		  if(i==0 && line[0]=='"') continue;
		  if(line[i]=='"'){ i++; flag=true; continue;}
		  movieName += line[i];
	  }
  }
  
  movieRating = stod(tempRating);
  return true;
}
