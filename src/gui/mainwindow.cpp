/**
 * @file mainwindow.cpp
 * @author Filip Januška
 * Implementation of the initial main window of the application
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(900,410);

    // TODO remove
    ui->input_ServerName->setText("localhost:1883");

    QObject::connect(
                ui->SaveButton, &QPushButton::clicked,
                this, &MainWindow::onAddConnection);

    QObject::connect(
                ui->DeleteButton, &QPushButton::clicked,
                this, &MainWindow::onRemoveConnection);

    QObject::connect(
                ui->ConnectButton, &QPushButton::clicked,
                this, &MainWindow::connectWindow);

    // Button group with all saved connections
    savedConnections = new QButtonGroup(ui->scrollConnections);
    // Only one may be selected at a time
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

    // New saved connection
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

    // Initialize the backend app logic
    app.create_client(serverName.toStdString());
    app.create_con_opts();
    app.create_callback();

    if (app.connect() != 0){
        ui->text_error->setText("Couldn't establish connection");
        ui->text_error->show();
        return;
    }
    // Switch control to the second window
    connectedWindow = new ConnectedWindow(ui->input_ServerName->text(), app, nullptr);
    this->hide();
    connectedWindow->show();

}
