#pragma once
#include "Media.h"

class Series : public Media {
private:
    int totalEpisodes;       // total de episódios
    int totalSeasons;        // total de temporadas
    int episodeDuration;     // duração de cada episódio em minutos

public:
    Series(const std::string& title, int year, int totalEps, int seasons, int epDur);

    int getTotalDuration() const override;  // total em minutos
    std::string getType() const override;
    bool isSeries() const override;

    int getTotalEpisodes() const;
    int getTotalSeasons() const;
    int getEpisodeDuration() const;
};
