/**
 * @file publishmessage.h
 * @author Filip Januška
 * Header for the publish message window of the application
 * Partly generated with Qt Creator
 */


#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include <QMainWindow>
#include <QFileDialog>

#include "../ApplicationLogic.h"

namespace Ui {
class PublishMessage;
}

/**
 * @class PublishMessage
 * @brief Represents the publish message window of the application
 *
 * This window pops up after a user clicks on the "Publish" button in the second application window.
 * It enables the user to create a message and send it to a specified topic, or upload a file to use
 * as message payload
 */
class PublishMessage : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * PublishMessage constructor
     * @param _app The backend logic of the application
     * @param topicName Name of the selected topic in the second app window
     * @param parent Parent widget
     */
    explicit PublishMessage(ApplicationLogic& _app, const QString& topicName, QWidget *parent = nullptr);
    /**
     * PublishMessage destructor
     */
    ~PublishMessage();

    /**
     * Launches a File Dialog window, for the user to select a file to upload.
     * The function then notifies the backend, which attempts to open and read the file.
     * The payload input field is disabled, when a file is selected.
     * If the file can't be read, an error message is displayed
     */
    void uploadFile();

    /**
     * Notifies the backend to publish a message. Topic is specified by user in an input field.
     * Payload is either specified bby user in an input field, or read from a file. Backend logic
     * decides, which one to use
     */
    void publish();

private:
    Ui::PublishMessage *ui;     /**< Application Ui */
    ApplicationLogic app;       /** Application backend logic */
};

#endif // PUBLISHMESSAGE_H
