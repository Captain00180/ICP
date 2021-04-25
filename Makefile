build: src/gui/MQTT_Explorer.pro
	cd src/gui; qmake-qt5 -o Makefile-gui; make -f Makefile-gui
# WARNING - "qmake-qt5" command must be changed to the system's version of qmake

run: build 
	src/gui/MQTT_Explorer

clean: 
	cd src/gui; make -f Makefile-gui clean; rm Makefile-gui; rm .qmake.stash; rm MQTT_Explorer

