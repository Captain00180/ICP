/**
 * @file camera.cpp
 * @author David Hurta (xhurta04)
 * @brief Source code for the Camera class.
 * @date 2021-04-29
 * 
 */

#include "camera.h"

Camera::Camera
(
    std::string topic_name,
    int interval_in_sec,
    std::string server,
    std::string directory_of_images,
    int number_of_pics
): Device::Device(topic_name, interval_in_sec, server)
{
    index = 0;
    number_of_pictures = 4;
    directory = directory_of_images;
    number_of_pictures = number_of_pics;
    buffer_size = 0;
    buffer_picture = nullptr;
}

Camera::~Camera()
{
    if (buffer_picture != nullptr)
    {
        delete[] buffer_picture;
    }
}

void Camera::generateStatus()
{
    generatePicture();
}

void Camera::generatePicture()
{
    if (buffer_picture == nullptr)
    {
        delete[] buffer_picture;
    }

    std::string filepath = directory + "/" + std::to_string(index) + ".jpg";
    std::ifstream ifs (filepath, std::ifstream::binary);
    index++;
    index = index % number_of_pictures;

    // https://www.cplusplus.com/reference/fstream/ifstream/rdbuf/
    // get pointer to associated buffer object
    std::filebuf* pbuf = ifs.rdbuf();

    // get file size using buffer's members
    std::size_t size = pbuf->pubseekoff (0,ifs.end,ifs.in);
    pbuf->pubseekpos (0,ifs.in);

    // allocate memory to contain file data
    char* buffer=new char[size];

    // get file data
    pbuf->sgetn (buffer,size);

    ifs.close();

    buffer_size = size;
    buffer_picture = buffer;
}

mqtt::message_ptr Camera::make_message()
{
    return mqtt::make_message(topic, buffer_picture, buffer_size);
}
