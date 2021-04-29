/**
 * @file camera.h
 * @author David Hurta (xhurta04)
 * @brief Header file for the Camera class.
 * @date 2021-04-29
 * 
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <iostream>
#include <fstream>

#include "device.h"

/**
 * @brief Class Camera represents a camera device.
 * 
 */
class Camera: public Device
{
    private:
        int index;
        int number_of_pictures;
        char* buffer_picture;
        double buffer_size;
        std::string directory;
        
        /**
         * @brief Loads the new picture to the buffer_picture and sets the buffer_size to its size.
         * Iterates indefinitely in pictures from "0.jpg" to "<number_of_pictures -1 >.jpg"
         */
        void generatePicture();

    public:
        /**
         * @brief Construct a new Camera object
         * 
         * @param topic_name 
         * @param interval_in_sec 
         * @param server 
         * @param directory             // Directory containing the images
         * @param number_of_pictures    // NUmber of images to iterate through
         */
        Camera
        (
            std::string topic_name,
            int interval_in_sec,
            std::string server,
            std::string directory,
            int number_of_pictures
        );

        /**
         * @brief Destroy the Camera object
         * 
         */
        ~Camera();

        /**
         * @brief Generates new picture.
         * 
         */
        void generateStatus() override;

        /**
         * @brief Creates a new message containing the picture.
         * 
         * @return mqtt::message_ptr 
         */
        mqtt::message_ptr make_message() override;
};

#endif //CAMERA_H
