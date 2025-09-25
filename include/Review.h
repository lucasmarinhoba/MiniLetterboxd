#pragma once
#include <string>
#include <memory>
#include "Media.h"

class Review {
private:
    std::shared_ptr<Media> media;
    int score;
    std::string text;
    std::string date; // "DD/MM/AAAA"

public:
    Review(std::shared_ptr<Media> media, int score, const std::string& text, const std::string& date);

    std::string getMediaTitle() const;
    int getScore() const;
    std::string getText() const;
    std::string getDate() const;
};
