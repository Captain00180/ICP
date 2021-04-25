#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class PublishMessage;
}

class PublishMessage : public QMainWindow
{
    Q_OBJECT

public:
    explicit PublishMessage(QString topicName, QWidget *parent = nullptr);
    ~PublishMessage();

    void uploadFile();

private:
    Ui::PublishMessage *ui;
    QString filePath;
};

#endif // PUBLISHMESSAGE_H
