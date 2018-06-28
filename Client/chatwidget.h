#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QMainWindow>
#include "../Data/userlist.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);

    void addParticipant(const QString &username);
    void setUserList(const QStringList &lst);
    void setUserList(const UserList &lst);
    void addMessage(const QString &msg);

    ~ChatWidget();

private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
