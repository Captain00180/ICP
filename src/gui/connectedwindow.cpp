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
    ui->topicsTree->header()->setStretchLastSection(false);
    ui->topicsTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);


    QObject::connect(
                ui->publishButton, &QPushButton::clicked,
                this, &ConnectedWindow::publishMessage);


    QObject::connect(
            ui->subscribeButton, &QPushButton::clicked,
            this, &ConnectedWindow::subscribe);

    QObject::connect(
            ui->topicsTree, &QTreeWidget::itemClicked,
            this, &ConnectedWindow::topicSelected
    );

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

    QObject::connect(
            ui->topicsTree, &QTreeWidget::itemClicked,
            this, &ConnectedWindow::topicSelected
            );


}

void ConnectedWindow::topicSelected() {
    QTreeWidgetItem* topic = ui->topicsTree->currentItem();

    QString top_name = topic->text(0);

    ui->text_TopicDetail->setText(top_name);

    std::vector<std::pair<std::string, std::string>> topic_history = app.get_topic_history(top_name.toStdString());
    ui->topicHistory->clear();
    for (auto i : topic_history)
    {
        auto timestamp = QString::fromStdString(i.first).simplified();
        QStringList timestampSplit = timestamp.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        auto payload = QString::fromStdString(i.second);
        ui->topicHistory->addItem(timestampSplit[3] + ": " + payload);
    }

}

void ConnectedWindow::displayMessage(const std::string topic_name, const std::string payload) {
    /*QList<QTreeWidgetItem*> topList = ui->topicsTree->findItems(QString::fromStdString(topic_name), Qt::MatchContains|Qt::MatchRecursive, 0);
    if (topList.length() != 0)
    {

        topList[0]->setText(1, QString::fromStdString(payload));
    }
    app.add_topic_message(topic_name, payload);
    */
    QString topicPath = QString::fromStdString(topic_name);
    if (topicPath.isEmpty())
    {
        return;
    }
    QStringList topicNameList = topicPath.split(QRegExp("/"), Qt::SkipEmptyParts);
    QList<QTreeWidgetItem*> topList = ui->topicsTree->findItems(topicNameList[0], Qt::MatchExactly, 0);

    QTreeWidgetItem* root = topList[0];
    int levelIndex = 1;
    int childIndex = 0;

    while (levelIndex < topicNameList.length() &&  childIndex < root->childCount())
    {
        auto kid = root->child(childIndex);
        if (kid->text(0) == topicNameList[levelIndex])
        {
            root = kid;
            childIndex = 0;
            levelIndex++;
        }
        else
        {
            childIndex++;
        }
    }
    if (levelIndex == topicNameList.length())
    {
        root->setText(1, QString::fromStdString(payload));
        app.add_topic_message(topic_name, payload);
    }

}

void ConnectedWindow::subscribeSuccess()
{
    QString topicPath = ui->input_topic->text();
    if (topicPath.isEmpty())
    {
        return;
    }

    QStringList topicNameList = topicPath.split(QRegExp("/"), Qt::SkipEmptyParts);
    for (auto i : topicNameList)
    {
        std::cerr << i.toStdString() << "__";
    }
    std::cerr << std::endl;
    QList<QTreeWidgetItem*> topList = ui->topicsTree->findItems(topicNameList[0], Qt::MatchExactly, 0);

    QTreeWidgetItem* root = nullptr;
    int levelIndex = 1;

    if (!topList.isEmpty())
    {

        root = topList[0];
        std::cerr << "Top level root already present - " << root->text(0).toStdString() << std::endl;
        int childIndex = 0;

        while (levelIndex < topicNameList.length() &&  childIndex < root->childCount())
        {

            auto kid = root->child(childIndex);
            std::cerr << "Checking child " << kid->text(0).toStdString() << std::endl;
            if (kid->text(0) == topicNameList[levelIndex])
            {
                std::cerr << "Match found: " << kid->text(0).toStdString() << std::endl;
                root = kid;
                childIndex = 0;
                levelIndex++;
            }
            else
            {
                childIndex++;
            }
        }
        if (levelIndex == topicNameList.length())
        {   // topic tree is already created - nothing to do
            return;
        }
    }
    else
    {
        // Create a top level root item
        root = new QTreeWidgetItem(ui->topicsTree);
        root->setText(0, topicNameList[0]);
        ui->topicsTree->addTopLevelItem(root);
    }

    QTreeWidgetItem* new_child = nullptr;
    for (; levelIndex < topicNameList.length(); levelIndex++)
    {
        new_child = new QTreeWidgetItem(root);
        new_child->setText(0, topicNameList[levelIndex]);
        root->addChild(new_child);
        root = new_child;

    }

    app.add_topic(topicPath.toStdString());
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
