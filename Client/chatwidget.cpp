#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    ui->LoadedImages->setVisible(false);


    connect(ui->actionStyle, SIGNAL(triggered(bool)),
            &dlg, SLOT(open()));

    connect(&dlg, SIGNAL(styleChanged(QFont&,QColor&)),
            this, SLOT(onStyleChanged(QFont&,QColor&)));
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

    /* reading text from UI */
    Message msg("You", text, style.getFont(), style.getColor());

    /* adding loaded image if it exists */
    if (!bufferedImage.isNull())
        msg.setImage(bufferedImage);

    /* set message to dialog UI */
    addMessage(msg);

    /* clear message line and loaded image label */
    ui->MessageLine->clear();
    ui->LoadedImages->clear();
    ui->LoadedImages->setVisible(false);

    /* send message to server */
    emit messageSent(msg);

    /* clear buffered image */
    bufferedImage = QPixmap();
}

void ChatWidget::on_loadImageButton_clicked()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Open image"),
                                             "", tr("*.png *.jpg *.jpeg"));
    auto imageName = path.split("/").last();
    QImage img;
    img.load(path);
    bufferedImage.fromImage(img);

    ui->LoadedImages->setVisible(true);
    ui->LoadedImages->setText("Selected image: " + imageName);
}

void ChatWidget::onStyleChanged(QFont &font, QColor &color)
{
    style.setFont(font);
    style.setColor(color);
}
