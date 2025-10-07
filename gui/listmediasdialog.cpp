#include "listmediasdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "Series.h" // necessário para dynamic_pointer_cast

ListMediasDialog::ListMediasDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), controller(ctrl)
{
    setupUI();
    populateMediaList();
}

void ListMediasDialog::setupUI() {
    setWindowTitle("Lista de Mídias");
    resize(400, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    mediaList = new QListWidget(this);
    layout->addWidget(mediaList);

    QPushButton* closeBtn = new QPushButton("Fechar", this);
    closeBtn->setMinimumHeight(40);
    closeBtn->setStyleSheet(
        "QPushButton { background-color: #2E3440; color: white; border-radius: 8px; font-size: 14px; }"
        "QPushButton:hover { background-color: #4C566A; }"
    );
    layout->addWidget(closeBtn);

    connect(closeBtn, &QPushButton::clicked, this, &ListMediasDialog::accept);
}

void ListMediasDialog::populateMediaList() {
    mediaList->clear();

    auto medias = controller->getMedias();
    for (const auto& m : medias) {
        QString type = m->isSeries() ? "Série" : "Filme";
        QString info;

        if (m->isSeries()) {
            auto s = std::dynamic_pointer_cast<Series>(m);
            info = QString("%1 - %2 (%3) - Duração: %4 min - Total de episódios: %5 - Temporadas: %6 - Média: %7")
                       .arg(QString::fromStdString(m->getTitle()))
                       .arg(type)
                       .arg(m->getYear())
                       .arg(s->getEpisodeDuration())
                       .arg(s->getTotalEpisodes())
                       .arg(s->getTotalSeasons())
                       .arg(m->getAverageScore(), 0, 'f', 1);
        } else {
            info = QString("%1 - %2 (%3) - Duração: %4 min - Média: %5")
                       .arg(QString::fromStdString(m->getTitle()))
                       .arg(type)
                       .arg(m->getYear())
                       .arg(m->getDuration())
                       .arg(m->getAverageScore(), 0, 'f', 1);
        }

        mediaList->addItem(info);
    }
}
