# Top level Makefile
# Author - Filip Januška
# Author - David Hurta
# Generates Makefiles for the main application and the traffic simulator, using qmake utility.

build: src/gui/MQTT_Explorer.pro
	cd src/gui; qmake -o Makefile-main; make -f Makefile-main
	cd src/traffic_simulator; qmake -o Makefile-sim; make -f Makefile-sim

# WARNING - "qmake-qt5" command must be changed to the system's version of qmake

run: build 
	src/gui/MQTT_Explorer

run-simulator: build
	cd src/traffic_simulator; ./traffic_simulator traffic_simulator.config

pack: clean
	zip -r 1-xhurta04-xjanus11.zip Makefile Doxyfile README.txt examples/* src/*.h src/*.cpp src/gui/*.h src/gui/*.cpp src/gui/*.ui src/gui/*.pro src/traffic_simulator/*.h src/traffic_simulator/*.cpp src/traffic_simulator/*.pro src/traffic_simulator/*.config

doxygen: Doxyfile
	doxygen Doxyfile

clean:
	rm -f 1-xhurta04-xjanus11.zip
	rm -rf ./doc/*	
	cd src/gui; make -f Makefile-main clean; rm -f Makefile-main; rm -f .qmake.stash; rm -f MQTT_Explorer 
	cd src/traffic_simulator; make -f Makefile-sim clean; rm -f Makefile-sim; rm -f .qmake.stash; rm -f traffic_simulator 
