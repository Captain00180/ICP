#include "connectedwindow.h"
#include "ui_connectedwindow.h"

ConnectedWindow::ConnectedWindow(QString serverName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    ui->setupUi(this);
    if (serverName.length() == 0)
        serverName = "Server Name";
    ui->text_ServerName->setText(serverName);

    QObject::connect(
                ui->publishButton, &QPushButton::clicked,
                this, &ConnectedWindow::publishMessage);
}

ConnectedWindow::~ConnectedWindow()
{
    delete ui;
}

void ConnectedWindow::publishMessage()
{
    this->setEnabled(false);
    publishMessageWindow = new PublishMessage(ui->text_TopicDetail->text());
    publishMessageWindow->show();
}
