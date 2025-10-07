#pragma once
#include <QDialog>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddFriendDialog; }
QT_END_NAMESPACE

class AddFriendDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddFriendDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~AddFriendDialog();

private slots:
    void onAddClicked();

private:
    Ui::AddFriendDialog* ui;
    AppController* controller;
};
