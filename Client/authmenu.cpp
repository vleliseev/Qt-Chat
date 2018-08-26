#include "authmenu.h"
#include "ui_authmenu.h"
#include <qDebug>


AuthMenu::AuthMenu(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::AuthMenu)
{
    ui->setupUi(this);
    ui->Login->setFont(QFont("Gadugi", 12));
    ui->Password->setFont(QFont("Gadugi", 12));
    ui->Password->setEchoMode(QLineEdit::Password);
}

AuthMenu::~AuthMenu()
{
    delete ui;
}


void
AuthMenu::on_SignButton_clicked()
{
    auto login = ui->Login->text();
    auto password = ui->Login->text();
    auto forbiddenCharacters = new QRegExp("[^a-zA-Z0-9]");

    if (login.isEmpty())
    {
        this->setStatus("Login is empty.");
        return;
    }

    if (login.contains(loginFilterPattern))
    {
        this->setStatus("Login contains forbidden characters.");
        return;
    }

    // Disable all buttons while making request to server
    ui->SignButton->setEnabled(false);
    ui->Login->setEnabled(false);
    ui->Password->setEnabled(false);

    // Show preloader gif until server response is catched
    auto preloader = new QMovie(":/Image/46.gif");
    preloader->start();
    ui->Status->setMovie(preloader);

    // Send signal with login and pass data
    // to network handler
    emit signIn(login, password);
}



void
AuthMenu::setStatus(const QString &status)
{
    ui->Status->setText(status);
    ui->SignButton->setEnabled(true);
    ui->Login->setEnabled(true);
    ui->Password->setEnabled(true);
}



void
AuthMenu::on_Login_returnPressed()
{
    on_SignButton_clicked();
}
