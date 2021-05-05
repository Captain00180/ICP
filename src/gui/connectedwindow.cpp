/**
 * @file connectedwindow.cpp
 * @author Filip Januška
 * @author David Hurta
 * Implementation of the second window of the application
 */


#include "connectedwindow.h"
#include "ui_connectedwindow.h"

ConnectedWindow::ConnectedWindow(QString serverName, ApplicationLogic& appLogic, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectedWindow)
{
    app = appLogic;
    ui->setupUi(this);

    ui->text_ServerName->setText(serverName);
    ui->topicsTree->setHeaderHidden(true);
    ui->topicsTree->setColumnCount(2);
    ui->topicsTree->header()->setStretchLastSection(false);
    ui->topicsTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);


    QObject::connect(
                ui->publishButton, &QPushButton::clicked,
                this, &ConnectedWindow::createMessage);


    QObject::connect(
            ui->subscribeButton, &QPushButton::clicked,
            this, &ConnectedWindow::subscribe);

    QObject::connect(
            ui->topicsTree, &QTreeWidget::itemClicked,
            this, &ConnectedWindow::topicSelected);

    QObject::connect(
            ui->copyTopicButton, &QPushButton::clicked,
            this, &ConnectedWindow::copyTopicName);

    QObject::connect(
            ui->unsubscribeButton, &QPushButton::clicked,
            this, &ConnectedWindow::unsubscribe);


    QObject::connect(
            app.active_callback_, &ActionCallback::subscribe_failed,
            this, &ConnectedWindow::subscribeFailed);

    QObject::connect(
            app.active_callback_, &ActionCallback::subscribe_success,
            this, &ConnectedWindow::subscribeSuccess);

    QObject::connect(
            app.active_callback_, SIGNAL(message_received(const std::string, const std::string)),
            this, SLOT(displayMessage(const std::string, const std::string)));

    QObject::connect(
                ui->snapshotButton, &QPushButton::clicked,
                this, &ConnectedWindow::saveSnapshot);

    // Register std::string type, so that it can be used in the displayMessage signal-slot connection
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
        // Only subscribe to a topic, if the name is valid
        return;
    }
    app.subscribe(text.toStdString());
}

void ConnectedWindow::unsubscribe() {
    QString topicPath = ui->text_TopicDetail->text();
    if (topicPath.isEmpty())
    {
        return;
    }
    ui->text_TopicDetail->setText("");
    ui->topicHistory->clear();
    delete ui->topicsTree->currentItem();
    app.unsubscribe(topicPath.toStdString());

}

void ConnectedWindow::topicSelected() {
    QTreeWidgetItem* topic = ui->topicsTree->currentItem();
    if (topic == nullptr)
    {
        return;
    }
    QString top_name = topic->text(0);
    topic = topic->parent();
    while (topic != nullptr)
    {
        // Iterate upwards through the topic tree to get the full path to the selected topic
        top_name = topic->text(0) + QString::fromStdString("/") + top_name;
        topic = topic->parent();
    }
    ui->text_TopicDetail->setText(top_name);

    // Fetch the topic history from the backend
    std::vector<std::pair<std::string, std::string>> topic_history = app.get_topic_history(top_name.toStdString());
    ui->topicHistory->clear();
    for (const auto& i : topic_history)
    {
        auto timestamp = QString::fromStdString(i.first).simplified();
        // Keep just the timestamp without date (HH:MM:SS)
        QStringList timestampSplit = timestamp.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
        auto payload = QString::fromStdString(i.second);
        ui->topicHistory->addItem(timestampSplit[3] + ": " + payload);
    }

}


void ConnectedWindow::copyTopicName() {
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->text_TopicDetail->text());
}

void ConnectedWindow::displayMessage(const std::string& topic_name, const std::string& payload) {

    QString topicPath = QString::fromStdString(topic_name);
    if (topicPath.isEmpty())
    {
        return;
    }
    // Split the topic path to separate topic levels
    QStringList topicNameList = topicPath.split(QRegExp("/"), Qt::SkipEmptyParts);
    // Search the top items in the topic tree for the required top level topic
    QList<QTreeWidgetItem*> topList = ui->topicsTree->findItems(topicNameList[0], Qt::MatchExactly, 0);

    QTreeWidgetItem* root = topList[0];
    // Current level in the topic path
    int levelIndex = 1;
    // Index of the currently checked out child topic
    int childIndex = 0;

    // Iterates through all children of a given topic, searching for the correct topic, according to the specified topic path
    while (levelIndex < topicNameList.length() &&  childIndex < root->childCount())
    {
        // Checks all children of the current topic
        auto kid = root->child(childIndex);
        if (kid->text(0) == topicNameList[levelIndex])
        {
            // The child topic is the next topic to follow, according to the path
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
        // The final topic fully matches the required topic path
        // This condition should be always true, it's here as a fail-safe
        QByteArray buffer = QByteArray(payload.data(), payload.length()-1);
        QPixmap pix_map = QPixmap();
        pix_map.loadFromData(buffer);
        if (!pix_map.toImage().isNull())    // Check if payload was an image
        {
            root->setText(1, "<Data Contains an Image>");
            // The image is saved into the second column of the item
            // Encoding the buffer content as to not lose any information when saving the image into a QString
            root->setText(2, QString(buffer.toBase64()));
        }
        else if (payload.length() > 20)
        {
            // Show only first 20 characters
            root->setText(1, QString::fromStdString(payload.substr(0, 20) + "..."));
            // The remaining data is saved into the second column
            root->setText(2, QString::fromStdString(payload));
        }
        else
        {
            root->setText(1, QString::fromStdString(payload));
            root->setText(2, QString::fromStdString(payload));
        }

        app.add_topic_message(topic_name, payload);
        // update the selected topic history
        topicSelected();
    }

}

void ConnectedWindow::subscribeSuccess()
{
    QString topicPath = ui->input_topic->text();
    if (topicPath.isEmpty())
    {
        return;
    }

    // Split the topic path to separate topic levels
    QStringList topicNameList = topicPath.split(QRegExp("/"), Qt::SkipEmptyParts);
    // Search the top items in the topic tree for the required top level topic
    QList<QTreeWidgetItem*> topList = ui->topicsTree->findItems(topicNameList[0], Qt::MatchExactly, 0);

    // Currently checked out topic
    QTreeWidgetItem* root = nullptr;
    // Current level in the topic path
    int levelIndex = 1;

    if (!topList.isEmpty())
    {
        // Top level topic is already present
        root = topList[0];
        int childIndex = 0;

        // Iterates through all children of a given topic, searching for the correct topic, according to the specified topic path
        while (levelIndex < topicNameList.length() &&  childIndex < root->childCount())
        {
            // Checks all children of the current topic
            auto kid = root->child(childIndex);
            if (kid->text(0) == topicNameList[levelIndex])
            {
                // The child topic is the next topic to follow, according to the path
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
            app.add_topic(topicPath.toStdString());
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
    // "root" is now set to the last created topic in the topic path
    // e.g. if topic path is "home/test/thermometer/front" and the hierarchy "home/test" is already created,
    // "root" will point to the "home/test" topic and create all subtopics left in the path

    QTreeWidgetItem* new_child = nullptr;
    for (; levelIndex < topicNameList.length(); levelIndex++)
    {
        // for all topics in the path which are not yet created, create them
        new_child = new QTreeWidgetItem(root);
        new_child->setText(0, topicNameList[levelIndex]);
        root->addChild(new_child);
        root = new_child;
    }

    app.add_topic(topicPath.toStdString());
}


// TODO Display it properly somewhere
void ConnectedWindow::subscribeFailed() {
    ui->disconnectButton->setText("Sub Failed");
}

void ConnectedWindow::createMessage()
{
    // Launches a Publish Message window, which blocks the rest of the app until it's closed
    publishMessageWindow = new PublishMessage(app, ui->text_TopicDetail->text());
    publishMessageWindow->show();
}

void ConnectedWindow::saveSnapshot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory); 
    std::string selected_dir = QFileDialog::getExistingDirectory(this, tr("Select the directory to save the snapshot")).toStdString();

    if (selected_dir.empty())
    {
        // user clicked cancel
        return;
    }

    QTreeWidget* tree = ui->topicsTree;
    QTreeWidgetItemIterator it(tree);
    while (*it)
    {
        // Get the path of the item
        std::string path = (*it)->text(0).toStdString();
        
        QTreeWidgetItem* parent = (*it)->parent();
        if (!parent)
        {
            path = (*it)->text(0).toStdString() + "/";
        }

        while (parent)
        {
            path = parent->text(0).toStdString() + "/" + path;
            parent = parent->parent();
        }

        path = selected_dir + "/" + path;
        std::experimental::filesystem::create_directories(path);


        // Create a jpg file if an image is detected
        // Create .txt file otherwise
        QByteArray buffer = QByteArray::fromBase64((*it)->text(2).toStdString().data(), QByteArray::Base64Encoding);
        QPixmap pix_map = QPixmap();
        pix_map.loadFromData(buffer);
        if (!pix_map.toImage().isNull())
        {
            path = path + "/payload.jpg";
            QFile file(path.c_str());
            file.open(QIODevice::WriteOnly);
            file.write(buffer);
            file.close();
        }
        else if (buffer.length() > 0)
        {
            std::ofstream file(path + "/payload.txt");
            file << (*it)->text(2).toStdString() << std::endl;
            file.close();
        }

        ++it;   // Next item
    }
}
