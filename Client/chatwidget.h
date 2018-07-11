#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>

#include "../Data/userlist.h"
#include "../Data/userdata.h"
#include "../Data/message.h"
#include "styledialog.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QMainWindow
{
    Q_OBJECT
public:

    explicit ChatWidget(QWidget *parent = 0);

    void addParticipant(const UserData &username);
    void removeParticipant(const QString &username);
    void addParticipants(const UserList &lst);
    void addMessage(const Message &msg);

    ~ChatWidget();

private slots:

    void on_SendButton_clicked();
    void on_loadImageButton_clicked();

    void onStyleChanged(QFont &font, QColor &color);

signals:

    void messageSent(Message &msg);

private:

    UserData style;
    Ui::ChatWidget *ui;
    QPixmap bufferedImage;
    StyleDialog dlg;
};

#endif // CHATWIDGET_H
