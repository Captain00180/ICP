CXX = g++
CXXFLAGS = -pedantic -g -Wall -Wextra -std=c++17

all: main

main: main.cpp action_callback.o Makefile
	$(CXX) $(CXXFLAGS) main.cpp action_callback.o -o main -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as

action_callback: action_callback.cpp action_callback.h
	$(CXX) $(CXXFLAGS) action_callback.cpp -c -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as

clean:
	rm main