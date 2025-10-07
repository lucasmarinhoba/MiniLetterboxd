#pragma once
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "Review.h"
#include "User.h"

class Media {
protected:
    std::string title;
    std::string synopsis;
    int year;
    int duration; // para filmes, para séries, pode ser usado como duração por episódio
    std::vector<std::string> cast;
    double ratingAverage;
    std::vector<std::shared_ptr<Review>> reviews;

public:
    Media(const std::string& t, int y, int d)
        : title(t), year(y), duration(d), ratingAverage(0.0) {}
    virtual ~Media() = default;

    // Métodos virtuais obrigatórios
    virtual int getTotalDuration() const = 0;
    virtual std::string getType() const = 0;
    virtual bool isSeries() const = 0;  

    // Getters
    std::string getTitle() const { return title; }
    int getYear() const { return year; }
    int getDuration() const { return duration; }
    std::string getSynopsis() const { return synopsis; }
    const std::vector<std::string>& getCast() const { return cast; }

    // Setters / Modifiers
    void setSynopsis(const std::string& text) { synopsis = text; }
    void addCastMember(const std::string& name) { cast.push_back(name); }

    void addReview(const std::shared_ptr<Review>& review);
    void removeReviewByUser(const std::shared_ptr<User>& user);

    const std::vector<std::shared_ptr<Review>>& getReviews() const { return reviews; }
    double getAverageScore() const { return ratingAverage; }

private:
    void updateRating();
};
