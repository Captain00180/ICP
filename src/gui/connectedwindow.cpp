#include "connectedwindow.h"
#include "ui_connectedwindow.h"

ConnectedWindow::ConnectedWindow(QString serverName, ApplicationLogic& appLogic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    app = appLogic;
    ui->setupUi(this);
    if (serverName.length() == 0)
        serverName = "Server Name";
    ui->text_ServerName->setText(serverName);

    ui->topicsTree->setHeaderHidden(true);
    ui->topicsTree->setColumnCount(2);


    QObject::connect(
                ui->publishButton, &QPushButton::clicked,
                this, &ConnectedWindow::publishMessage);


    QObject::connect(
            ui->subscribeButton, &QPushButton::clicked,
            this, &ConnectedWindow::subscribe);

    QObject::connect(
            app.active_callback_, &ActionCallback::subscribe_failed,
            this, &ConnectedWindow::subscribeFailed);

    QObject::connect(
            app.active_callback_, &ActionCallback::subscribe_success,
            this, &ConnectedWindow::subscribeSuccess);

    QObject::connect(
            app.active_callback_, SIGNAL(message_received(const std::string, const std::string)),
            this, SLOT(displayMessage(const std::string, const std::string)));

    qRegisterMetaType<std::string>("std::string");


}

ConnectedWindow::~ConnectedWindow()
{
    delete ui;
}

void ConnectedWindow::subscribe() {
    QString text = ui->input_topic->text();
    if (text.length() == 0)
    {
        return;
    }
    app.subscribe(text.toUtf8().constData());
}

void ConnectedWindow::addTopic(const std::string& name) {
    QTreeWidgetItem* topic = new QTreeWidgetItem(ui->topicsTree);
    topic->setText(0, QString::fromStdString(name));
    topic->setText(1, "Hello");
    ui->topicsTree->addTopLevelItem(topic);
    QTreeWidgetItem* child = new QTreeWidgetItem(topic);
    child->setText(0, "I'm a child");
    topic->addChild(child);
    ui->topicsTree->resizeColumnToContents(0);

}

void ConnectedWindow::displayMessage(const std::string topic_name, const std::string payload) {
    QList<QTreeWidgetItem*> clist = ui->topicsTree->findItems(QString::fromStdString(topic_name), Qt::MatchContains|Qt::MatchRecursive, 0);
    std::cout << "FRONTEND: " << topic_name << " : " << payload << std::endl;
    if (clist.length() != 0)
    {

        clist[0]->setText(1, QString::fromStdString(payload));
    }
}

void ConnectedWindow::subscribeSuccess()
{
    std::string topicName = ui->input_topic->text().toUtf8().constData();
    if (!app.topic_subscribed(topicName))
    {
        std::cerr << "Adding topic\n";
        app.add_topic(topicName);
        addTopic(topicName);
    }
}

void ConnectedWindow::subscribeFailed() {
    ui->disconnectButton->setText("Sub Failed");
}

void ConnectedWindow::publishMessage()
{
    this->setEnabled(false);
    publishMessageWindow = new PublishMessage(ui->text_TopicDetail->text());
    publishMessageWindow->show();
}
