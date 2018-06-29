#ifndef AUTHMENU_H
#define AUTHMENU_H

#include <QMainWindow>
#include <QString>
#include <QMovie>

namespace Ui {
class AuthMenu;
}

class AuthMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthMenu(QWidget *parent = 0);
    ~AuthMenu();

    void setStatus(const QString &status);

signals:

    void signIn(const QString &username, const QString &password);

private slots:

    void on_SignButton_clicked();
    void on_Login_returnPressed();

private:
    Ui::AuthMenu *ui;
};

#endif // AUTHMENU_H
