#include "AddFriendDialog.h"
#include "ui_AddFriendDialog.h"
#include <QMessageBox>

AddFriendDialog::AddFriendDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::AddFriendDialog), controller(ctrl)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &AddFriendDialog::onAddClicked);
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

void AddFriendDialog::onAddClicked()
{
    QString username = ui->usernameEdit->text().trimmed();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Digite o nome do usuário!");
        return;
    }

    std::string msg;
    if (controller->addFriend(username.toStdString(), msg)) {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        accept();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
