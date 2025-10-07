#include "AddSeriesDialog.h"
#include "./ui_AddSeriesDialog.h"
#include <QMessageBox>

AddSeriesDialog::AddSeriesDialog(QWidget* parent, AppController* ctrl)
    : QDialog(parent), ui(new Ui::AddSeriesDialog), controller(ctrl)
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &AddSeriesDialog::onAddClicked);
}

AddSeriesDialog::~AddSeriesDialog()
{
    delete ui;
}

void AddSeriesDialog::onAddClicked()
{
    QString title = ui->lineEditTitle->text();
    QString yearStr = ui->lineEditYear->text();
    QString durationStr = ui->lineEditEpisodeDuration->text();
    QString seasonsStr = ui->lineEditSeasons->text();
    QString episodesStr = ui->lineEditEpisodesPerSeason->text();

    if (title.isEmpty() || yearStr.isEmpty() || durationStr.isEmpty() ||
        seasonsStr.isEmpty() || episodesStr.isEmpty())
    {
        QMessageBox::warning(this, "Erro", "Preencha todos os campos!");
        return;
    }

    bool okYear, okDuration, okSeasons, okEpisodes;
    int year = yearStr.toInt(&okYear);
    int duration = durationStr.toInt(&okDuration);
    int seasons = seasonsStr.toInt(&okSeasons);
    int episodes = episodesStr.toInt(&okEpisodes);

    if (!okYear || !okDuration || !okSeasons || !okEpisodes ||
        year <= 1800 || duration <= 0 || seasons <= 0 || episodes <= 0)
    {
        QMessageBox::warning(this, "Erro", "Valores inválidos!");
        return;
    }

    int totalEpisodes = episodes * seasons;
    std::string msg;

    // Ordem correta da assinatura: title, year, totalEpisodes, totalSeasons, episodeDuration, message
    if (controller->addSeries(title.toStdString(), year, totalEpisodes, seasons, duration, msg)) {
        QMessageBox::information(this, "Sucesso", QString::fromStdString(msg));
        accept();
    } else {
        QMessageBox::warning(this, "Erro", QString::fromStdString(msg));
    }
}
