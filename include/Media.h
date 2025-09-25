#pragma once
#include <string>
#include <vector>

class Media {
protected:
    std::string title;
    std::string synopsis;
    int year;
    int duration; // minutos
    std::vector<std::string> cast;
    double ratingAverage;

public:
    Media(const std::string& title, int year, int duration);

    virtual ~Media() = default;
    virtual int getTotalDuration() const = 0;

    std::string getTitle() const;
    void setSynopsis(const std::string& text);
    void addCastMember(const std::string& name);
    void updateRating(double newRating);

    double getRatingAverage() const;
};
