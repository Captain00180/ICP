CXX = g++
CXXFLAGS = -pedantic -g -Wall -Werror -std=c++17

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

clean:
	rm main