#include "mainform.h"
#include "ui_mainform.h"


MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm),
    networkManager(new ConnectionHandler())
{
    ui->setupUi(this);
    connect(networkManager, SIGNAL(userConnected(QString)), this, SLOT(on_Connection(QString)));
    connect(networkManager, SIGNAL(userDisconnected(QString)), this, SLOT(on_Connection(QString)));

}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_ClearLog_clicked()
{
    ui->Log->clear();
}

void MainForm::on_StartButton_clicked()
{
    /* do nothing is server is already started */
    if (networkManager->isListening()) return;

    /* else start server and update logs */
    networkManager->startServer();
    ui->Status->setText("Status: on");
    ui->Log->addItem(getCurrentTime() + "|Server started at localhost.");
}

void MainForm::on_StopButton_clicked()
{
    /* if there's nothing to stop, we do nothing */
    if (!networkManager->isListening()) return;

    /* else stop server and update logs */
    networkManager->stopServer();
    ui->Status->setText("Status: off");
    ui->Log->addItem(getCurrentTime() + "|Server stopped.");
    ui->Log->addItem(getCurrentTime() + "|All users disconnected.");
    ui->ClientLog->clear();
}

QString MainForm::getCurrentTime() const
{
    return QTime::currentTime().toString();
}

void MainForm::on_Connection(QString username)
{
    ui->Log->addItem(getCurrentTime() + "|User" + username + " connected.");
}

void MainForm::on_Disconnection(QString username)
{
    ui->Log->addItem(getCurrentTime() + "|User" + username + " disconnected.");
}
