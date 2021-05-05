/**
 * @file connectedwindow.h
 * @author Filip Januška
 * @author David Hurta
 * 
 * Header for the second window of the application
 * Partly generated with Qt Creator
 */

#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <QMainWindow>
#include <QTreeWidget>
#include <QClipboard>
#include "publishmessage.h"
#include "../ApplicationLogic.h"
#include "../ActionCallback.h"

namespace Ui {
class ConnectedWindow;
}

/**
 * @class ConnectedWindow
 * @brief Represents the second window of the application
 *
 * This window is the most important one. It displays all information after a client is connected, including the
 * topics in a tree hierarchy, topic detail and control buttons for publishing, saving the state, subscribing etc.
 */
class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * ConnectedWindow constructor
     * @param serverName Name of the server, to which the client is connected
     * @param appLogic Backend application logic
     * @param parent Parent widget
     */
    ConnectedWindow(QString serverName, ApplicationLogic& appLogic, QWidget *parent);

    /**
     * ConnectedWindow destructor
     */
    ~ConnectedWindow();

    /**
     * Creates a publishmessage window after user clicks on the "Publish" button.
     * The publishmessage window is modal, meaning that the rest of the application is
     * disabled, until user finishes work in the publishmessage window.
     */
    void createMessage();

    /**
     * Notifies the backend to subscribe to a topic, specified by user in an input field.
     */
    void subscribe();

    /**
     * Notifies the backend to unsubscribe from the selected topic. Deletes the topic from the topic tree structure.
     */
    void unsubscribe();

    /**
     * Triggers when user selects a topic in the tree structure. The topic's history and detail is displayed on the right
     * side of the app.
     */
    void topicSelected();

    /**
     * Saves the snapshot of the MQTT tree topics.
     * Users is asked to provide a directory, where the snapshot will be saved to.
     * Snapshot contains folders representing topics. If a topic contained any data, the data is saved to a payload.txt file
     * in the corresponding directory for the topic. If an image is recognized, the image is saved to a payload.jpg file.
     */
    void saveSnapshot();

    /**
     * Copies the selected topic's name to system clipboard.
     */
    void copyTopicName();

public slots:
    /**
     * Receives a signal from the application callback handler when a subscribe action is successful.
     * Adds the topic to the topic tree structure, creating the hierarchy as necessary.
     * Then it notifies the backend, to register the topic as subscribed.
     */
    void subscribeSuccess();

    /**
     * Receives a signal from the application callback handler when a subscribe action fails.
     * Displays an error message
     */
    void subscribeFailed();

    /**
     * Receives a signal from the application callback handler when client receives a message.
     * It locates the corresponding topic in the tree hierarchy and displays the payload next to it.
     * If this topic is currently selected, its history is updated.
     * The backend is then notified to save the topic message.
     * @param topic_name Name of the topic
     * @param payload Message payload
     */
    void displayMessage(const std::string&, const std::string&);

private:
    Ui::ConnectedWindow *ui;    /**< Application Ui */
    PublishMessage* publishMessageWindow;   /**< Pointer to a publishmessage window */
    ApplicationLogic app;   /**< Application backend logic */
};

#endif // CONNECTEDWINDOW_H
