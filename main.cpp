#include <iostream>
#include <string>
#include "paho.mqtt.cpp/src/mqtt/async_client.h" //!!! Set to your path to your pacho library
#include "action_callback.h"


int main(int argc, char* argv[])
{
    std::cout << "Connect to server: ";
    std::string server ;
    std::cin >> server;

    mqtt::async_client cli(server, "ICP_testing_client_20");

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    action_callback cb(cli);
    cli.set_callback(cb);
    try {
        std::cout << "Connecting to the server..." << std::flush;
        cli.connect(connOpts, nullptr, cb)->wait();
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "\nError: Unable to connect to MQTT server: \t" << exc << std::endl;
        return 1;
    }

    while(1)
    {
        std::string msg ;
        std::cin >> msg;

        if (msg == "p") {
            cb.print_messages = false;
            std::cin >> msg;

            if(msg == "publish")
            {
                std::string topic;
                std::string payload;

                std::cout << "Topic: ";
                std::cin >> topic;
                std::cout << "Payload: ";
                std::cin >> payload;
                auto message = mqtt::make_message(topic, payload);
                cli.publish(message, nullptr, cb);
            }
            else if(msg == "q")
                break;
            else if(msg == "subscribe")
            {
                std::string topic;
                std::cout << "Topic: ";
                std::cin >> topic;

                cli.subscribe(topic, 1, nullptr, cb);
            }
            else if(msg == "unsubscribe")
            {
                std::string topic;
                std::cout << "Topic: ";
                std::cin >> topic;

                cli.unsubscribe(topic);
            }
            cb.print_messages = true;
        }
    }

    try{
        std::cout << "Disconnecting from the MQTT server..." << std::flush;
        cli.disconnect()->wait();
        std::cout << "OK\n";
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc << std::endl;
        return 1;
    }
    return 0;
}