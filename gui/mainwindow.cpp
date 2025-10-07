#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHBoxLayout>
#include "registerdialog.h"
#include "usermenuwindow.h"

MainWindow::MainWindow(AppController* ctrl, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(ctrl)
{
    ui->setupUi(this);

    // Tamanho fixo da janela
    setFixedSize(800, 600);

    // Status bar
    this->statusBar()->showMessage("Projeto Final POO 25.1 - UFPB - Lucas Marinho Basilio de Sousa");
    this->statusBar()->setStyleSheet("color: gray; font-size: 10px; padding-left: 10px;");

    // Conexões dos botões
    connect(ui->btnRegister, &QPushButton::clicked, this, &MainWindow::onRegisterClicked);
    connect(ui->btnLogin, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);

    // Estilizar e centralizar botões como no UserMenuWindow
    QList<QPushButton*> mainButtons = { ui->btnRegister, ui->btnLogin, ui->btnExit };

    for (auto btn : mainButtons) {
        btn->setFixedWidth(200); // largura padronizada
        btn->setStyleSheet(
            "QPushButton { background-color: #2E3440; color: white; border-radius: 8px; font-size: 14px; padding: 6px 12px; }"
            "QPushButton:hover { background-color: #4C566A; }"
        );

        // Centraliza o botão horizontalmente
        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->addStretch();
        hLayout->addWidget(btn);
        hLayout->addStretch();

        // Remove o botão do layout antigo e adiciona no novo layout centralizado
        ui->verticalLayout->removeWidget(btn);
        ui->verticalLayout->addLayout(hLayout);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRegisterClicked()
{
    RegisterDialog dialog(this, controller);
    dialog.exec();
}

void MainWindow::onLoginClicked()
{
    bool ok;
    QString username = QInputDialog::getText(this, "Login", "Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;

    QString password = QInputDialog::getText(this, "Login", "Password:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) return;

    std::string message;
    if(controller->login(username.toStdString(), password.toStdString(), message)) {
        QMessageBox::information(this, "Login", QString::fromStdString(message));
        UserMenuWindow* userWindow = new UserMenuWindow(*controller);
        userWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(message));
    }
}

void MainWindow::onExitClicked()
{
    close();
}
