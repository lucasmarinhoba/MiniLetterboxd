#include "User.h"
#include <algorithm> // std::remove_if

// Construtor
User::User(const std::string& uname, const std::string& pwd)
    : username(uname), password(pwd) {}

// Getters básicos
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

bool User::checkPassword(const std::string& pass) const {
    return pass == password;
}

// Amigos
void User::addFriend(std::shared_ptr<User> user) {
    if (!user) return;
    for (auto& f : friends) {
        if (auto fptr = f.lock()) {
            if (fptr->getUsername() == user->getUsername()) return; // já existe
        }
    }
    friends.push_back(user);
}

std::vector<std::weak_ptr<User>> User::getFriends() const {
    return friends;
}

// Reviews
void User::addReview(std::shared_ptr<Review> review) {
    if (!review) return;

    // Garante que a review tem usuário associado
    if (!review->getUser()) {
        throw std::invalid_argument("Review deve ter um usuário associado");
    }

    reviews.push_back(review);

    // Atualiza mídias assistidas
    if (auto media = review->getMedia()) {
        if (std::find(watchedMedias.begin(), watchedMedias.end(), media) == watchedMedias.end()) {
            watchedMedias.push_back(media);
        }
    }
}

void User::removeReview(const std::string& mediaTitle) {
    reviews.erase(std::remove_if(reviews.begin(), reviews.end(),
        [&mediaTitle](const std::shared_ptr<Review>& r) {
            return r && r->getMediaTitle() == mediaTitle;
        }), reviews.end());
}

std::vector<std::shared_ptr<Review>> User::getReviews() const {
    return reviews;
}

// Mídias assistidas
void User::addWatchedMedia(std::shared_ptr<Media> media) {
    if (!media) return;
    if (std::find(watchedMedias.begin(), watchedMedias.end(), media) == watchedMedias.end()) {
        watchedMedias.push_back(media);
    }
}

size_t User::getWatchedCount() const {
    return watchedMedias.size();
}

std::string User::getLastReviewInfo() const {
    if (reviews.empty()) return "Nenhuma review";
    auto last = reviews.back();
    return last->getMediaTitle() + " (" + std::to_string(last->getScore()) + ")";
}

double User::getTotalWatchTimeHours() const {
    int totalMinutes = 0;
    for (auto& m : watchedMedias) {
        if (m) totalMinutes += m->getTotalDuration();
    }
    return totalMinutes / 60.0;
}
