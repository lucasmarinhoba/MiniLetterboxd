#pragma once
#include <QDialog>
#include <QPushButton>
#include <QString>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeleteFriendDialog; }
QT_END_NAMESPACE

class DeleteFriendDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteFriendDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~DeleteFriendDialog();

    std::function<void()> onSuccess; // callback chamado após exclusão bem-sucedida

private slots:
    void onDeleteClicked();

private:
    Ui::DeleteFriendDialog* ui;
    AppController* controller;
};
