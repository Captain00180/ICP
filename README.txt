ICP Project: MQTT explorer/dashboard
Authors:    David Hurta     - xhurta04
            Filip Januška   - xjanus11
2020/2021
-----------------------------------------------
The MQTT explorer app provides an interface for mqtt communication. It allows the user
to connect to a server, subscribe to desired topics and publish messages. Topics and 
their messages are displayed in a tree hierarchy, with each topic keeping a history
of its messages, which can be displayed by clicking on a topic.

Part of the solution is a traffic simulator, which simulates various devices, sending and
receiving simple mqtt communication. 
-----------------------------------------------
Implementation details

-The app can connect to a specified server and follow user desired topics
-The subscribed topics are displayed in a tree hierarchy structure, which displays
	the last message sent to the topic. Backend keeps a history of messages for
	each topic. 
-The app is able to receive basic text payload or binary data, in which case it tries
	to interpret the data as an image and display it in a separate window when 
	the user double clicks on the topic. Long text can also be displayed in 
	a window upon double clicking the topic. 
-User can create new topics by subscribing to a topic with the desired name. 
-User can publish a message to any topic. The message can be either a text input, or
	a file uploaded by user. 
-User can save a snapshot of the current state of the client, with all subscribed topics
	and their potential payloads.
-User can set actuator's status via publishing a message in a format "set:X", where X 
    is representing a corresponding value (example: to turn off a relay, user publishes 
    on the device's topic a message "set:off"; to set a thermostat's value the message
    would be "set:X°C" where X is an integer)

-The traffic simulator allows the user to simulate mqtt traffic, by simulating smart devices
	sending and receiving messages. The simulator can be configured by a .config file,
	which is passed to it as a required parameter. The structure of a config file is 
	demonstrated in examples/traffic_simulator.config

Unimplemented functionality

-The first window allows the user to save and load server connection presets. While this works
	in the UI, the app doesn't actually save or load these presets between app launches. 
-Due to inaccurate time and difficulty assessment, we weren't able to implement the Dashboard.
	Only the UI elements are present, with no real functionality. 
----------------------------------------------
Notes

-Compilation is done using qmake, which is called from the top level Makefile. 
-"make" to compile, "make run" to launch the main application
-Qt version 5.15
-Eclipse paho mqtt library for C/C++
-Traffic simulator can be run with the run-simulator Makefile target
