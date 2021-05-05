/**
 * @file publishmessage.cpp
 * @author Filip Januška
 * Implementation of the publish message window of the application
 */

#include "publishmessage.h"
#include "ui_publishmessage.h"

PublishMessage::PublishMessage(ApplicationLogic& _app, const QString& topicName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublishMessage)
{
    app = _app;
    app.reset_file_status();

    ui->setupUi(this);
    ui->input_topicName->setText(topicName);

    QObject::connect(
                ui->uploadButton, &QPushButton::clicked,
                this, &PublishMessage::uploadFile);

    QObject::connect(
            ui->publishButton, &QPushButton::clicked,
            this, &PublishMessage::publish);

}

PublishMessage::~PublishMessage()
{
    delete ui;
}

void PublishMessage::uploadFile()
{
    // Launches a File Dialog, where user can select any file to upload
    QString filePath = QFileDialog::getOpenFileName(
                this, "Upload File",
                "");

    if (filePath.isEmpty())
    {
        return;
    }

    QFileInfo* fileName = new QFileInfo(filePath);
    if (!app.open_file(filePath.toStdString()))
    {
        // Attempts to open and read the file in backend logic
        ui->text_fileName->setText("Failed to open file");
    }
    else
    {
        ui->text_fileName->setText("Selected file: " + fileName->fileName());
        ui->input_payload->setEnabled(false);
    }

}

void PublishMessage::publish() {
    QString payload = ui->input_payload->toPlainText();
    QString topic = ui->input_topicName->text();
    if ((!app.is_file_selected() && payload.isEmpty()) || topic.isEmpty())
    {
        // Doesn't do anything if the user input field is empty or the topic name is not provided
        return;
    }

    // Default QoS
    int qos = 0;

    if (ui->qos_1->isChecked())
    {
        qos = 1;
    }
    if (ui->qos_2->isChecked())
    {
        qos = 2;
    }

    app.publish(topic.toStdString(), payload.toStdString(), qos, ui->retainCheck->isChecked());
    this->close();
}
