#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::addParticipant(const QString &username)
{
    ui->Users->addItem(username);
}

void ChatWidget::addMessage(const QString &msg)
{
    auto item = new QListWidgetItem;
    item->setTextColor(Qt::red);
    item->setText(msg);
    ui->Dialog_2->addItem(item);
}

void ChatWidget::addParticipants(const UserList &lst)
{
    auto users = lst.getUsers();
    for (auto &user : users) this->addParticipant(user);
}

void ChatWidget::removeParticipant(const QString &username)
{
    auto removeItem = ui->Users->findItems(username, Qt::MatchFixedString).at(0);
    delete removeItem;
}
