#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent)
    : QMainWindow(parent),
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



void
ChatWidget::addParticipant(const UserData &username)
{
    auto participant = new QListWidgetItem;
    participant->setFont(username.getFont());
    participant->setTextColor(username.getColor());
    participant->setText(username.getUsername());

    // Disable selecting participant in list widget
    participant->setFlags(participant->flags() & ~Qt::ItemIsSelectable);
    ui->Users->addItem(participant);
}



void
ChatWidget::addMessage(const Message &msg)
{
    auto item = new QListWidgetItem;
    item->setTextColor(msg.getTextColor());
    item->setFont(msg.getTextFont());
    item->setText(msg.getSender() + ":" + msg.getMessage());

    // Disable selecting message in dialog
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    ui->Dialog_2->addItem(item);
}



void
ChatWidget::addParticipants(const UserList &lst)
{
    auto users = lst.getUsers();
    for (auto &user : users) this->addParticipant(user);
}



void
ChatWidget::removeParticipant(const QString &username)
{
    auto itemToRemove = ui->Users->findItems(username, Qt::MatchFixedString).at(0);
    delete itemToRemove;
}



void
ChatWidget::on_SendButton_clicked()
{
    auto text = ui->MessageLine->toPlainText();
    if (text.isEmpty()) return;

    /* todo: user can select font and color of his message */
    /* msg.setTextColor(...); msg.setFontColor(...); */

    Message msg("You", text, style.getFont(), style.getColor());

    // If user has loaded any image, add it to Message data
    if (!bufferedImage.isNull()) msg.setImage(bufferedImage);

    // Add message to dialog widget
    addMessage(msg);

    // Clear message line and loaded image label
    ui->MessageLine->clear();
    ui->LoadedImages->clear();
    ui->LoadedImages->setVisible(false);

    // Send message to server
    emit messageSent(msg);

    // Clear buffered image
    bufferedImage = QPixmap();
}



void
ChatWidget::on_loadImageButton_clicked()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Open image"),
                                             "", tr("*.png *.jpg *.jpeg"));
    // Get image name from string
    auto imageName = path.split("/").last();

    // Load image to UI
    QImage img;
    img.load(path);
    bufferedImage.fromImage(img);

    // Make UI visible
    ui->LoadedImages->setVisible(true);
    ui->LoadedImages->setText("Selected image: " + imageName);
}



void
ChatWidget::onStyleChanged(QFont &font, QColor &color)
{
    style.setFont(font);
    style.setColor(color);
}
