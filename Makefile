CXX = g++
CXXFLAGS = -pedantic -g -Wall -Wextra -std=c++17

all: main

main: main.cpp action_callback.o application_logic.o Makefile
	$(CXX) $(CXXFLAGS) main.cpp action_callback.o application_logic.o -o main -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as

action_callback: action_callback.cpp action_callback.h
	$(CXX) $(CXXFLAGS) action_callback.cpp -c -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as


application_logic: application_logic.cpp application_logic.h
	$(CXX) $(CXXFLAGS) application_logic.cpp -c -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as

clean:
	rm main ./*.o