#include "publishmessage.h"
#include "ui_publishmessage.h"

PublishMessage::PublishMessage(QString topicName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublishMessage)
{
    ui->setupUi(this);

    ui->input_topicName->setText(topicName);

    QObject::connect(
                ui->uploadButton, &QPushButton::clicked,
                this, &PublishMessage::uploadFile);


}

PublishMessage::~PublishMessage()
{
    delete ui;
}

void PublishMessage::uploadFile()
{
    filePath = QFileDialog::getOpenFileName(
                this, "Upload File",
                "", tr("Text files (*.txt)"));

    QFileInfo* fileName = new QFileInfo(filePath);
    ui->text_fileName->setText("Selected file: " + fileName->fileName());
    ui->input_payload->setPlainText(filePath);
}
