#include "styledialog.h"
#include "ui_styledialog.h"

StyleDialog::StyleDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StyleDialog),
    userFont(QFont("Gadugi", 12)),
    userColor(QColor(Qt::red))
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    QString pattern = tr("<font color='%1'>%2</font>");
    ui->Pattern->setText(pattern.arg(userColor.name(), "Pattern"));
    ui->Pattern->setFont(userFont);

    ui->currentColor->setText("Current color: " + userColor.name());
    ui->currentFont->setText("Current font: " + userFont.family());

}

StyleDialog::~StyleDialog()
{
    delete ui;
}



void
StyleDialog::on_selectFont_clicked()
{
    bool ok;
    userFont = QFontDialog::getFont(&ok, this);
    ui->Pattern->setFont(userFont);
    ui->currentFont->setText("Current font: " + userFont.family());
}



void
StyleDialog::on_selectColor_clicked()
{
    userColor = QColorDialog::getColor(Qt::red, this);

    QString pattern = tr("<font color='%1'>%2</font>");
    ui->Pattern->setText(pattern.arg(userColor.name(), "Pattern"));
    ui->currentColor->setText("Current color: " + userColor.name());
}



void
StyleDialog::on_pushButton_clicked()
{
    emit styleChanged(userFont, userColor);
    this->close();
}
