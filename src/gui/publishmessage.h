#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include <QMainWindow>
#include <QFileDialog>

#include "../ApplicationLogic.h"

namespace Ui {
class PublishMessage;
}

class PublishMessage : public QMainWindow
{
    Q_OBJECT

public:
    explicit PublishMessage(ApplicationLogic& _app, QString topicName, QWidget *parent = nullptr);
    ~PublishMessage();

    void uploadFile();

    void publish();

private:
    Ui::PublishMessage *ui;
    QString filePath;
    ApplicationLogic app;
};

#endif // PUBLISHMESSAGE_H
