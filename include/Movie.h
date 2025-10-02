#pragma once
#include "Media.h"

class Movie : public Media {
public:
    Movie(const std::string& t, int y, int d)
        : Media(t, y, d) {}

    int getTotalDuration() const override {
        return duration;
    }

    std::string getType() const override {
        return "Movie";
    }
};