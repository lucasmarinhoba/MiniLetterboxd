#pragma once

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include "AppController.h"

class DeleteReviewDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteReviewDialog(QWidget* parent, AppController* controller);

    std::function<void()> onSuccess; // callback após exclusão

private slots:
    void onDeleteClicked();
    void onCancelClicked();

private:
    AppController* controller;

    QLabel* titleLabel;
    QComboBox* mediaSelector;
    QPushButton* deleteButton;
    QPushButton* cancelButton;

    void setupUI();
    void populateMedias();
};
