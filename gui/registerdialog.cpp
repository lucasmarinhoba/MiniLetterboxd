#include "registerdialog.h"
#include "./ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent, AppController* ctrl)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
    , controller(ctrl)
{
    ui->setupUi(this);
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterDialog::onRegisterClicked);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onRegisterClicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos!");
        return;
    }

    std::string msg;
    if(controller->registerUser(username.toStdString(), password.toStdString(), msg)) {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        accept(); // fecha o diálogo
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
