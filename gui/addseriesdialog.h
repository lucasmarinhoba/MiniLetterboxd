#pragma once
#include <QDialog>
#include "AppController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddSeriesDialog; }
QT_END_NAMESPACE

class AddSeriesDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddSeriesDialog(QWidget* parent = nullptr, AppController* ctrl = nullptr);
    ~AddSeriesDialog();

private slots:
    void onAddClicked();

private:
    Ui::AddSeriesDialog* ui;
    AppController* controller;
};
