#pragma once
#include <QMainWindow>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AppController* ctrl, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRegisterClicked();
    void onLoginClicked();
    void onExitClicked();

private:
    Ui::MainWindow *ui;
    AppController* controller;
};
