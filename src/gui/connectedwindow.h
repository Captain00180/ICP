#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "publishmessage.h"
#include "../application_logic.h"
#include "../action_callback.h"

namespace Ui {
class ConnectedWindow;
}

class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConnectedWindow(QString serverName, application_logic& appLogic, QWidget *parent);
    ~ConnectedWindow();

    void publishMessage();

    void subscribe();

    void addTopic(const std::string& name);

public slots:
    void subscribeSuccess();
    void subscribeFailed();
    void displayMessage(const std::string, const std::string);

private:
    Ui::ConnectedWindow *ui;
    PublishMessage* publishMessageWindow;
    application_logic app;
};

#endif // CONNECTEDWINDOW_H
