#pragma once

#include <QDialog>
#include <QListWidget>
#include "AppController.h"

class ListMediasDialog : public QDialog {
    Q_OBJECT

public:
    explicit ListMediasDialog(QWidget* parent, AppController* ctrl);

private:
    AppController* controller;
    QListWidget* mediaList;

    void setupUI();
    void populateMediaList();
};
