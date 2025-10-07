#pragma once

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include "AppController.h"

class FriendActivityDialog : public QDialog {
    Q_OBJECT

public:
    explicit FriendActivityDialog(QWidget* parent, AppController* ctrl, const std::string& friendUsername);

private:
    AppController* controller;
    std::string friendName;
    QListWidget* activityList;

    void setupUI();
    void populateActivity();
};
