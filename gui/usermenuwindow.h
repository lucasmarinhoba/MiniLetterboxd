#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "AppController.h"

class UserMenuWindow : public QWidget {
    Q_OBJECT

public:
    explicit UserMenuWindow(AppController& ctrl, QWidget* parent = nullptr);

private:
    AppController& controller;

    QLabel* usernameLabel;
    QLabel* totalWatchedLabel;
    QLabel* lastReviewLabel;
    QLabel* totalHoursLabel;
    QLabel* totalFriendsLabel;

    QPushButton* addMovieBtn;
    QPushButton* addSeriesBtn;
    QPushButton* addReviewBtn;
    QPushButton* deleteReviewBtn;
    QPushButton* addFriendBtn;
    QPushButton* deleteFriendBtn;
    QPushButton* listFriendsBtn;
    QPushButton* listMediasBtn;
    QPushButton* friendActivityBtn;
    QPushButton* userPageBtn;
    QPushButton* logoutBtn;

    void setupUI();
    void connectSignals();
    void updateUserInfo();
};
