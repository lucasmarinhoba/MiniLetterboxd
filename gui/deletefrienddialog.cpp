#include "DeleteFriendDialog.h"
#include "./ui_DeleteFriendDialog.h"
#include <QMessageBox>

DeleteFriendDialog::DeleteFriendDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::DeleteFriendDialog), controller(ctrl)
{
    ui->setupUi(this);
    connect(ui->deleteButton, &QPushButton::clicked, this, &DeleteFriendDialog::onDeleteClicked);
}

DeleteFriendDialog::~DeleteFriendDialog() {
    delete ui;
}

void DeleteFriendDialog::onDeleteClicked() {
    QString username = ui->usernameEdit->text();
    if(username.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Informe o nome do amigo!");
        return;
    }

    std::string msg;
    if(controller->deleteFriend(username.toStdString(), msg)) {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        if(onSuccess) onSuccess(); // chama callback para atualizar a UserMenuWindow
        accept();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
