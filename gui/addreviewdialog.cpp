#include "AddReviewDialog.h"
#include "./ui_AddReviewDialog.h"
#include <QMessageBox>

AddReviewDialog::AddReviewDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::AddReviewDialog), controller(ctrl)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate()); // Inicializa com a data atual
    ui->dateEdit->setDisplayFormat("dd/MM/yyyy");
    connect(ui->btnAdd, &QPushButton::clicked, this, &AddReviewDialog::onAddClicked);
}

AddReviewDialog::~AddReviewDialog()
{
    delete ui;
}

void AddReviewDialog::onAddClicked()
{
    QString mediaTitle = ui->lineEditMediaTitle->text();
    QString reviewText = ui->textEditReview->toPlainText();
    QString ratingStr  = ui->lineEditRating->text();
    QDate reviewDate = ui->dateEdit->date();

    if(mediaTitle.isEmpty() || reviewText.isEmpty() || ratingStr.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos!");
        return;
    }

    bool ok;
    int rating = ratingStr.toInt(&ok);
    if(!ok || rating < 0 || rating > 10) {
        QMessageBox::warning(this, "Erro", "A nota deve ser um número entre 0 e 10!");
        return;
    }

    std::string msg;
    if(controller->addReview(
        mediaTitle.toStdString(),
        rating,
        reviewText.toStdString(),
        reviewDate.toString("dd/MM/yyyy").toStdString(),
        msg))
    {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        accept();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
