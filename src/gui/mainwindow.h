#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "connectedwindow.h"

#include "../application_logic.h"
#include "../action_callback.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onAddConnection();

    void onRemoveConnection();

    void onSelectSaved();

    void connectWindow();

/*
public slots:
    void failedToConnect();
*/

private:
    application_logic app;
    Ui::MainWindow *ui;
    QButtonGroup* savedConnections;
    ConnectedWindow* connectedWindow;

};
#endif // MAINWINDOW_H
