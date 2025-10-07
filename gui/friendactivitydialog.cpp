#include "FriendActivityDialog.h"
#include <QVBoxLayout>

FriendActivityDialog::FriendActivityDialog(QWidget* parent, AppController* ctrl, const std::string& friendUsername)
    : QDialog(parent), controller(ctrl), friendName(friendUsername)
{
    setupUI();
    populateActivity();
}

void FriendActivityDialog::setupUI() {
    setWindowTitle(QString::fromStdString("Atividade de " + friendName));
    resize(400, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    activityList = new QListWidget(this);
    layout->addWidget(activityList);

    QPushButton* closeBtn = new QPushButton("Fechar", this);
    closeBtn->setMinimumHeight(40);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #2E3440; color: white; border-radius: 8px; font-size: 14px; }"
        "QPushButton:hover { background-color: #4C566A; }"
    );
    layout->addWidget(closeBtn);

    connect(closeBtn, &QPushButton::clicked, this, &FriendActivityDialog::accept);
}

void FriendActivityDialog::populateActivity() {
    activityList->clear();

    QStringList activities = controller->getFriendLastActivity(friendName);
    if (activities.isEmpty()) {
        activityList->addItem("Nenhuma atividade encontrada.");
        return;
    }

    for (const QString& act : activities) {
        activityList->addItem(act);
    }
}
