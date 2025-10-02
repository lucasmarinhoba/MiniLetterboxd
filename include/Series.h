#pragma once
#include "Media.h"
#include <vector>
#include <string>

class Series : public Media {
private:
    int episodeDuration;                   // duração de cada episódio em minutos
    std::vector<int> episodesPerSeason;    // número de episódios por temporada

public:
    // Construtor principal
    Series(const std::string& t, int y, int epDur, const std::vector<int>& episodes)
        : Media(t, y, 0),   // duração inicial 0; getTotalDuration() calcula depois
          episodeDuration(epDur),
          episodesPerSeason(episodes) {}

    // Construtor sobrecarregado (apenas 3 parâmetros)
    Series(const std::string& t, int y, int epDur)
        : Series(t, y, epDur, {}) {}

    // Adiciona uma temporada com quantidade de episódios
    void addSeason(int episodes) {
        episodesPerSeason.push_back(episodes);
    }

    // Retorna a duração total de todos os episódios
    int getTotalDuration() const override {
        int total = 0;
        for (auto e : episodesPerSeason) total += e * episodeDuration;
        return total;
    }

    // Retorna tipo da mídia
    std::string getType() const override {
        return "Series";
    }

    // Getter para episódios por temporada
    const std::vector<int>& getEpisodesPerSeason() const { return episodesPerSeason; }
};
