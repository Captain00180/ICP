#ifndef CONNECTEDWINDOW_H
#define CONNECTEDWINDOW_H

#include <QMainWindow>
#include "publishmessage.h"

namespace Ui {
class ConnectedWindow;
}

class ConnectedWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectedWindow(QString serverName="Server Name", QWidget *parent = nullptr);
    ~ConnectedWindow();

    void publishMessage();

private:
    Ui::ConnectedWindow *ui;
    PublishMessage* publishMessageWindow;
};

#endif // CONNECTEDWINDOW_H
