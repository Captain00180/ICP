/**
 * @file mainwindow.h
 * @author Filip Januška
 * Header for the initial main window of the application
 * Partly generated with Qt Creator
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "connectedwindow.h"

#include "../ApplicationLogic.h"
#include "../ActionCallback.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Represents the first window of the application
 *
 * The first window pops up on application launch and enables the user to connect to a specified mqtt server,
 * save and load server connection presets.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * MainWindow constructor
     * @param parent Pointer to a parent widget
     */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * MainWindow destructor
     */
    ~MainWindow();

    /**
     * Creates a new button, holding the name of a server, based on the user input.
     * The button can be clicked to load the server name, or deleted.
     */
    void onAddConnection();

    /**
     * Deletes the selected saved connection.
     */
    void onRemoveConnection();

    /**
     * Loads the server name from the selected saved connection widget.
     */
    void onSelectSaved();

    /**
     * Sends a connection request to the backend and waits for the result of the action.
     * If connection attempt is successful, the window is hidden, a second application window is created and shown.
     * If connection fails, an error message is displayed.
     */
    void connectWindow();


private:
    ApplicationLogic app;   /**< The backend logic of the application */
    Ui::MainWindow *ui;     /**< The Ui of the application */
    QButtonGroup* savedConnections;     /**< Buttongroup containing all saved connections */
    ConnectedWindow* connectedWindow;   /** Pointer to a second window of the application. It's initialised when a connection is established */

};
#endif // MAINWINDOW_H
