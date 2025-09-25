#pragma once
#include "Media.h"
#include <vector>

class Series : public Media {
private:
    int seasons;
    std::vector<int> episodesPerSeason;
    int episodeDuration;

public:
    Series(const std::string& title, int year, int episodeDuration);

    void addSeason(int episodes);
    int getTotalDuration() const override;
};
