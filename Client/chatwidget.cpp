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

void ChatWidget::addParticipant(const UserData &username)
{
    auto participant = new QListWidgetItem;
    participant->setFont(username.getFont());
    participant->setTextColor(username.getColor());
    participant->setText(username.getUsername());
    ui->Users->addItem(participant);
}

void ChatWidget::addMessage(const Message &msg)
{
    auto item = new QListWidgetItem;
    item->setTextColor(msg.getTextColor());
    item->setFont(msg.getTextFont());
    item->setText(msg.getSender() + ":" + msg.getMessage());
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

void ChatWidget::on_SendButton_clicked()
{
    auto text = ui->MessageLine->toPlainText();
    if (text.isEmpty()) return;

    /* todo: user can select font and color of his message */
    /* msg.setTextColor(...); msg.setFontColor(...); */
    /* todo: user can upload any image from computer and send it */
    /* msg.setImage(...); */

    /* add message to UI */
    Message msg("You", text);
    addMessage(msg);
    ui->MessageLine->clear();

    /* send message to server */
    emit messageSent(msg);
}
