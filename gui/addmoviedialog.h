#pragma once
#include <QDialog>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddMovieDialog; }
QT_END_NAMESPACE

class AddMovieDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddMovieDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~AddMovieDialog();

private slots:
    void onAddClicked();

private:
    Ui::AddMovieDialog* ui;
    AppController* controller;
};
