#pragma once
#include "Media.h"

class Movie : public Media {
public:
    Movie(const std::string& title, int year, int duration);
    int getTotalDuration() const override;
};
