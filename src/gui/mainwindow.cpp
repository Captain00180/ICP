#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(900,410);
    QPushButton* butt_create = ui->SaveButton;

    QObject::connect(
                butt_create, &QPushButton::clicked,
                this, &MainWindow::onAddConnection);

    QObject::connect(
                ui->DeleteButton, &QPushButton::clicked,
                this, &MainWindow::onRemoveConnection);

    QObject::connect(
                ui->ConnectButton, &QPushButton::clicked,
                this, &MainWindow::connectWindow);

    savedConnections = new QButtonGroup(ui->scrollConnections);
    savedConnections->setExclusive(true);

    ui->text_error->hide();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddConnection()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->verticalLayout_4);

    QString text = ui->input_ServerName->text();

    QPushButton* new_button = new QPushButton(text, ui->scrollConnections);
    new_button->setMinimumSize(QSize(250, 50));
    new_button->setCheckable(true);

    QObject::connect(
                new_button, &QPushButton::clicked,
                this, &MainWindow::onSelectSaved);

    layout->insertWidget(0, new_button);
    savedConnections->addButton(new_button);
    new_button->setChecked(true);


}

void MainWindow::onRemoveConnection()
{
    QPushButton* del_button = qobject_cast<QPushButton*>(savedConnections->checkedButton());
    delete del_button;
    ui->input_ServerName->setText("");
}

void MainWindow::onSelectSaved()
{
    QPushButton* button = qobject_cast<QPushButton*>(savedConnections->checkedButton());
    QString text = button->text();
    ui->input_ServerName->setText(text);
}

void MainWindow::connectWindow()
{

    QString serverName = ui->input_ServerName->text();
    if (serverName.length() == 0)
    {
        ui->text_error->setText("Invalid Server Name");
        ui->text_error->show();
        return;
    }
    else
        ui->text_error->hide();

    app.create_client(serverName.toUtf8().constData(), "RandomICPId");
    app.create_con_opts();
    app.create_callback();
    app.connect();


    connectedWindow = new ConnectedWindow(ui->input_ServerName->text());
    this->hide();
    connectedWindow->show();

}
