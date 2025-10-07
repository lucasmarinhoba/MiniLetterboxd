#pragma once
#include <QDialog>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddReviewDialog; }
QT_END_NAMESPACE

class AddReviewDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddReviewDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~AddReviewDialog();

private slots:
    void onAddClicked();

private:
    Ui::AddReviewDialog* ui;
    AppController* controller;
};
