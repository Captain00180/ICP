build: src/gui/MQTT_Explorer.pro
	cd src/gui; qmake-qt5 -o Makefile-main; make -f Makefile-main
	cd src/traffic_simulator; qmake-qt5 -o Makefile-sim; make -f Makefile-sim

# WARNING - "qmake-qt5" command must be changed to the system's version of qmake

run: build 
	src/gui/MQTT_Explorer

clean: 
	cd src/gui; make -f Makefile-main clean; rm Makefile-main; rm .qmake.stash; rm MQTT_Explorer
	cd src/traffic_simulator; make -f Makefile-sim clean; rm Makefile-sim; rm .qmake.stash; rm traffic_simulator

