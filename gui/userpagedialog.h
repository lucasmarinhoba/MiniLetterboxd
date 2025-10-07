#pragma once
#include <QLabel>
#include <QTextEdit>
#include <QDialog>
#include <QPushButton>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserPageDialog; }
QT_END_NAMESPACE

class UserPageDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserPageDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~UserPageDialog();

private:
    Ui::UserPageDialog* ui;
    AppController* controller;

    QLabel* usernameLabel;
    QLabel* totalWatchedLabel;
    QLabel* lastReviewLabel;
    QLabel* totalHoursLabel;
    QLabel* totalFriendsLabel;
    QTextEdit* reviewTextEdit;
    QPushButton* btnClose;

    void updateUserInfo();
    void setupUI();
    void connectSignals();
};
