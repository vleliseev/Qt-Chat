#include "authmenu.h"
#include "ui_authmenu.h"


#include <qDebug>

AuthMenu::AuthMenu(QWidget *parent) :
    QMainWindow(parent),
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

void AuthMenu::on_SignButton_clicked()
{
    if (ui->Login->text().isEmpty())
    {
        this->setStatus("Login is empty.");
        return;
    }
    ui->SignButton->setEnabled(false);
    ui->Login->setEnabled(false);
    ui->Password->setEnabled(false);

    auto preloader = new QMovie(":/Image/46.gif");
    ui->Status->setMovie(preloader);
    preloader->start();
    emit signIn(ui->Login->text(), ui->Password->text());
}

void AuthMenu::setStatus(const QString &status)
{
    ui->Status->setText(status);
    ui->SignButton->setEnabled(true);
    ui->Login->setEnabled(true);
    ui->Password->setEnabled(true);
}

void AuthMenu::on_Login_returnPressed()
{
    on_SignButton_clicked();
}
