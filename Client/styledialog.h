#ifndef STYLEDIALOG_H
#define STYLEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QFontDialog>


namespace Ui {
class StyleDialog;
}

class StyleDialog : public QDialog
{
    Q_OBJECT
public:

    explicit StyleDialog(QWidget *parent = 0);
    ~StyleDialog();

signals:

    void styleChanged(QFont&, QColor&);

private slots:

    void on_selectFont_clicked();
    void on_selectColor_clicked();
    void on_pushButton_clicked();

private:

    Ui::StyleDialog *ui;

    QFont userFont;
    QColor userColor;
};

#endif // STYLEDIALOG_H
