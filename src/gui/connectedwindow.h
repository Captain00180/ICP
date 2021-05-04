#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

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

class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConnectedWindow(QString serverName, ApplicationLogic& appLogic, QWidget *parent);
    ~ConnectedWindow();

    void publishMessage();

    void subscribe();

    void unsubscribe();

    void addTopic(const std::string& name);

    void topicSelected();

    void copyTopicName();

public slots:
    void subscribeSuccess();
    void subscribeFailed();
    void displayMessage(const std::string, const std::string);

private:
    Ui::ConnectedWindow *ui;
    PublishMessage* publishMessageWindow;
    ApplicationLogic app;
};

#endif // CONNECTEDWINDOW_H
