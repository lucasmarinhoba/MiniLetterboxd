#include "Media.h"

void Media::addReview(const std::shared_ptr<Review>& review) {
    if (review) {
        reviews.push_back(review);
        updateRating();
    }
}

void Media::removeReviewByUser(const std::shared_ptr<User>& user) {
    if (!user) return;
    reviews.erase(std::remove_if(reviews.begin(), reviews.end(),
                [&](const std::shared_ptr<Review>& r){
                    return r && r->getUser() == user;
                }), reviews.end());
    updateRating();
}

void Media::updateRating() {
    if (reviews.empty()) {
        ratingAverage = 0.0;
        return;
    }
    double sum = 0.0;
    for (const auto& r : reviews) {
        if (r) sum += r->getScore();
    }
    ratingAverage = sum / reviews.size();
}
