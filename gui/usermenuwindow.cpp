#include "UserMenuWindow.h"
#include "UserPageDialog.h"
#include "AddMovieDialog.h"
#include "AddSeriesDialog.h"
#include "AddReviewDialog.h"
#include "DeleteReviewDialog.h"
#include "AddFriendDialog.h"
#include "DeleteFriendDialog.h"
#include "ListMediasDialog.h"
#include "FriendActivityDialog.h"
#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>

UserMenuWindow::UserMenuWindow(AppController& ctrl, QWidget* parent)
    : QWidget(parent), controller(ctrl)
{
    setFixedSize(800, 600);
    setupUI();
    connectSignals();
    updateUserInfo();

    QLabel* footerLabel = new QLabel(
        "Projeto Final POO 25.1 - UFPB\nLucas Marinho Basilio de Sousa", this);
    footerLabel->setStyleSheet("color: gray; font-size: 10px;");
    footerLabel->setGeometry(10, 570, 780, 30);
    footerLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    footerLabel->setWordWrap(true);
}

void UserMenuWindow::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    usernameLabel = new QLabel(this);
    totalWatchedLabel = new QLabel(this);
    lastReviewLabel = new QLabel(this);
    totalHoursLabel = new QLabel(this);
    totalFriendsLabel = new QLabel(this);

    QFont infoFont;
    infoFont.setPointSize(11);
    infoFont.setBold(true);

    usernameLabel->setFont(infoFont);
    totalWatchedLabel->setFont(infoFont);
    lastReviewLabel->setFont(infoFont);
    totalHoursLabel->setFont(infoFont);
    totalFriendsLabel->setFont(infoFont);

    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(totalWatchedLabel);
    mainLayout->addWidget(lastReviewLabel);
    mainLayout->addWidget(totalHoursLabel);
    mainLayout->addWidget(totalFriendsLabel);

    // Botões
    addMovieBtn = new QPushButton("Adicionar Filme", this);
    addSeriesBtn = new QPushButton("Adicionar Série", this);
    addReviewBtn = new QPushButton("Adicionar Review", this);
    deleteReviewBtn = new QPushButton("Remover Review", this);
    addFriendBtn = new QPushButton("Adicionar Amigo", this);
    deleteFriendBtn = new QPushButton("Remover Amigo", this);
    listFriendsBtn = new QPushButton("Listar Amigos", this);
    listMediasBtn = new QPushButton("Listar Mídias", this);
    friendActivityBtn = new QPushButton("Atividade de amigo", this);
    userPageBtn = new QPushButton("Minha Página", this);
    logoutBtn = new QPushButton("Logout", this);

    QList<QPushButton*> buttons = {
        addMovieBtn, addSeriesBtn, addReviewBtn, deleteReviewBtn,
        addFriendBtn, deleteFriendBtn, listFriendsBtn, listMediasBtn,
        friendActivityBtn, userPageBtn, logoutBtn
    };

    for (auto btn : buttons) {
        btn->setFixedWidth(200);
        btn->setStyleSheet(
            "QPushButton { background-color: #2E3440; color: white; border-radius: 8px; font-size: 14px; padding: 6px 12px; }"
            "QPushButton:hover { background-color: #4C566A; }"
        );

        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->addStretch();
        hLayout->addWidget(btn);
        hLayout->addStretch();
        mainLayout->addLayout(hLayout);
    }
}

void UserMenuWindow::connectSignals() {
    connect(addMovieBtn, &QPushButton::clicked, [this]() {
        AddMovieDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(addSeriesBtn, &QPushButton::clicked, [this]() {
        AddSeriesDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(addReviewBtn, &QPushButton::clicked, [this]() {
        AddReviewDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(deleteReviewBtn, &QPushButton::clicked, [this]() {
        DeleteReviewDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(addFriendBtn, &QPushButton::clicked, [this]() {
        AddFriendDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(deleteFriendBtn, &QPushButton::clicked, [this]() {
        DeleteFriendDialog dialog(this, &controller);
        dialog.exec();
        updateUserInfo();
    });

    connect(listFriendsBtn, &QPushButton::clicked, [this]() {
        auto user = controller.getLoggedUser();
        if (!user) return;

        QString friendsStr;
        for (auto& fWeak : user->getFriends()) {
            if (auto f = fWeak.lock()) {
                friendsStr += QString::fromStdString(f->getUsername()) + "\n";
            }
        }
        if (friendsStr.isEmpty()) friendsStr = "Nenhum amigo adicionado.";
        QMessageBox::information(this, "Amigos", friendsStr);
    });

    connect(listMediasBtn, &QPushButton::clicked, [this]() {
        ListMediasDialog dialog(this, &controller);
        dialog.exec();
    });

    connect(friendActivityBtn, &QPushButton::clicked, [this]() {
        bool ok;
        QString friendName = QInputDialog::getText(this, "Última atividade de amigo",
                                                   "Digite o nome do amigo:", QLineEdit::Normal, "", &ok);
        if (ok && !friendName.isEmpty()) {
            FriendActivityDialog dialog(this, &controller, friendName.toStdString());
            dialog.exec();
        }
    });

    connect(userPageBtn, &QPushButton::clicked, [this]() {
        auto user = controller.getLoggedUser();
        if (!user) {
            QMessageBox::warning(this, "Aviso", "Nenhum usuário logado.");
            return;
        }
        UserPageDialog* dialog = new UserPageDialog(this, &controller);
        dialog->setModal(true);
        dialog->show();
    });

    connect(logoutBtn, &QPushButton::clicked, [this]() {
        this->close();
        MainWindow* loginWindow = new MainWindow(&controller);
        loginWindow->show();
    });
}

void UserMenuWindow::updateUserInfo() {
    auto user = controller.getLoggedUser();
    if (!user) return;

    usernameLabel->setText(QString::fromStdString("Usuário: " + user->getUsername()));
    totalWatchedLabel->setText(QString("Filmes/Séries assistidos: %1").arg(user->getWatchedCount()));
    lastReviewLabel->setText(QString::fromStdString("Última review: " + user->getLastReviewInfo()));
    totalHoursLabel->setText(QString("Tempo total assistido: %1 horas").arg(user->getTotalWatchTimeHours()));
    totalFriendsLabel->setText(QString("Amigos: %1").arg(user->getFriends().size()));
}
