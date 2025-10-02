#pragma once
#include <string>
#include <vector>
#include <memory>

class Review;

class Media {
protected:
    std::string title;
    std::string synopsis;
    int year;
    int duration; // minutos
    std::vector<std::string> cast;
    double ratingAverage;
    std::vector<std::shared_ptr<Review>> reviews;

public:
    // Construtor com nomes de parâmetros distintos para evitar shadowing
    Media(const std::string& t, int y, int d)
        : title(t), year(y), duration(d), ratingAverage(0.0) {}

    virtual ~Media() = default;
    virtual int getTotalDuration() const = 0;

    std::string getTitle() const { return title; }
    int getYear() const { return year; }

    void setSynopsis(const std::string& text) { synopsis = text; }
    void addCastMember(const std::string& name) { cast.push_back(name); }

    virtual std::string getType() const = 0;

    void addReview(const std::shared_ptr<Review>& review) {
        reviews.push_back(review);
        updateRating();
    }

    const std::vector<std::shared_ptr<Review>>& getReviews() const { return reviews; }
    double getAverageScore() const { return ratingAverage; }

private:
    // Atualiza a média considerando todos os reviews
    void updateRating() {
        if (reviews.empty()) {
            ratingAverage = 0.0;
            return;
        }
        double sum = 0.0;
        for (auto& r : reviews) sum += r->getScore();
        ratingAverage = sum / reviews.size();
    }
};
