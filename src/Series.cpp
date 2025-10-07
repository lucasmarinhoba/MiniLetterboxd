#include "Series.h"

Series::Series(const std::string& t, int y, int totalEps, int seasons, int epDur)
    : Media(t, y, totalEps * epDur),   // duração total agora está correta
      totalEpisodes(totalEps),
      totalSeasons(seasons),
      episodeDuration(epDur) {}

int Series::getTotalDuration() const {
    return totalEpisodes * episodeDuration; // total em minutos
}

std::string Series::getType() const {
    return "Series";
}

bool Series::isSeries() const {
    return true;
}

int Series::getTotalEpisodes() const { 
    return totalEpisodes; 
}

int Series::getTotalSeasons() const { 
    return totalSeasons; 
}

int Series::getEpisodeDuration() const { 
    return episodeDuration; 
}
