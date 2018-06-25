#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QTime>

#include "connectionhandler.h"
#include "datahandler.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    QString getCurrentTime() const;
    ~MainForm();

private slots:

    void on_Connection(QString username);
    void on_Disconnection(QString username);
    void on_ClearLog_clicked();
    void on_StartButton_clicked();
    void on_StopButton_clicked();

private:
    Ui::MainForm *ui;
    ConnectionHandler *networkManager;
};

#endif // MAINFORM_H
