#include "UserPageDialog.h"
#include "ui_UserPageDialog.h"
#include <QScrollBar>

UserPageDialog::UserPageDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::UserPageDialog), controller(ctrl)
{
    ui->setupUi(this);
    setFixedSize(800, 600);

    // Conectar botão fechar
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::accept);

    updateUserInfo();
}

UserPageDialog::~UserPageDialog() {
    delete ui;
}

void UserPageDialog::updateUserInfo() {
    auto user = controller->getLoggedUser();
    if (!user) return;

    // Atualiza informações do usuário
    ui->labelUsername->setText(QString("👤 Usuário: %1").arg(QString::fromStdString(user->getUsername())));
    ui->labelWatchedCount->setText(QString("🎥 Filmes/Séries assistidos: %1").arg(user->getWatchedCount()));
    ui->labelLastReview->setText(QString("📝 Última review: %1").arg(QString::fromStdString(user->getLastReviewInfo())));
    ui->labelTotalHours->setText(QString("⏱️ Tempo total assistido: %1 horas").arg(user->getTotalWatchTimeHours()));
    ui->labelTotalFriends->setText(QString("👥 Amigos: %1").arg(user->getFriends().size()));

    // Atualiza todas as reviews no QTextEdit
    ui->textReviews->clear();

    if (user->getReviews().empty()) {
        ui->textReviews->setText("Nenhuma review registrada.");
    } else {
        for (auto& rev : user->getReviews()) {
            QString reviewText = QString(
                "🎬 %1\n⭐ Nota: %2\n📝 %3\n📅 %4\n\n"
            )
            .arg(QString::fromStdString(rev->getMediaTitle()))
            .arg(rev->getScore())
            .arg(QString::fromStdString(rev->getText()))
            .arg(QString::fromStdString(rev->getDate()));

            ui->textReviews->append(reviewText);
        }

        // Mantém o scroll no topo
        ui->textReviews->verticalScrollBar()->setValue(0);
    }
}
