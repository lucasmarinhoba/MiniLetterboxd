#include "AddMovieDialog.h"
#include "./ui_AddMovieDialog.h"
#include <QMessageBox>

AddMovieDialog::AddMovieDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::AddMovieDialog), controller(ctrl)
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &AddMovieDialog::onAddClicked);
}

AddMovieDialog::~AddMovieDialog()
{
    delete ui;
}

void AddMovieDialog::onAddClicked()
{
    QString title = ui->lineEditTitle->text();
    QString yearStr = ui->lineEditYear->text();
    QString durationStr = ui->lineEditDuration->text();

    if(title.isEmpty() || yearStr.isEmpty() || durationStr.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos!");
        return;
    }

    bool okYear, okDuration;
    int year = yearStr.toInt(&okYear);
    int duration = durationStr.toInt(&okDuration);

    if(!okYear || !okDuration || year <= 1800 || duration <= 0) {
        QMessageBox::warning(this, "Erro", "Valores inválidos!");
        return;
    }

    std::string msg;
    if(controller->addMovie(title.toStdString(), year, duration, msg)) {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        accept();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
