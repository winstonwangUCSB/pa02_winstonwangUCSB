#Makefile

CXX = g++

CXX_FLAG = --std=c++11 -g

all: runMovies

runMovies: main.o movies.o
	$(CXX) $(CXX_FLAG) main.o movies.o -o runMovies 

movies.o: movies.cpp
	$(CXX) -c $(CXX_FLAG) movies.cpp

main.o: main.cpp
	$(CXX) -c $(CXX_FLAG) main.cpp

clean:
	rm -f runMovies *o
