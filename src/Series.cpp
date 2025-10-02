#include "Series.h"

// Construtor sobrecarregado
Series::Series(const std::string& t, int y, int epDur)
    : Series(t, y, epDur, {}) {}

// Adiciona uma temporada com quantidade de episódios
void Series::addSeason(int episodes) {
    episodesPerSeason.push_back(episodes);
}

// Retorna a duração total de todos os episódios
int Series::getTotalDuration() const {
    int total = 0;
    for (auto e : episodesPerSeason) total += e * episodeDuration;
    return total;
}

// Retorna tipo da mídia
std::string Series::getType() const {
    return "Series";
}

// Getter para episódios por temporada
const std::vector<int>& Series::getEpisodesPerSeason() const {
    return episodesPerSeason;
}
