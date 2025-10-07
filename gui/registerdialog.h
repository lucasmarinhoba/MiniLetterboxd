#pragma once
#include <QDialog>
#include "AppController.h"

namespace Ui { class RegisterDialog; }

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent, AppController* ctrl);
    ~RegisterDialog();

private slots:
    void onRegisterClicked();

private:
    Ui::RegisterDialog *ui;
    AppController* controller;
};
