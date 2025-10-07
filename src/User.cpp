#include "User.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>  // para std::round

// Construtor
User::User(const std::string& uname, const std::string& pwd)
    : username(uname), password(pwd) {}

// ----- Getters básicos -----
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
bool User::checkPassword(const std::string& pass) const { return pass == password; }

// ----- Amigos -----
void User::addFriend(std::shared_ptr<User> user) {
    if (!user) return;
    for (auto& f : friends) {
        if (auto fptr = f.lock()) {
            if (fptr->getUsername() == user->getUsername()) return; // já existe
        }
    }
    friends.push_back(user);
}

bool User::removeFriend(const std::string& username) {
    auto it = std::remove_if(friends.begin(), friends.end(),
                             [&](const std::weak_ptr<User>& f){
                                 if (auto fptr = f.lock()) return fptr->getUsername() == username;
                                 return false;
                             });
    if (it != friends.end()) {
        friends.erase(it, friends.end());
        return true;
    }
    return false;
}

std::shared_ptr<User> User::getFriend(const std::string& username) const {
    for (auto& f : friends) {
        if (auto fptr = f.lock()) {
            if (fptr->getUsername() == username) return fptr;
        }
    }
    return nullptr;
}

std::vector<std::weak_ptr<User>> User::getFriends() const { return friends; }

// ----- Reviews -----
void User::addReview(std::shared_ptr<Review> review) {
    if (!review) return;
    if (!review->getUser()) throw std::invalid_argument("Review deve ter um usuário associado");
    reviews.push_back(review);

    // Atualiza mídias assistidas
    if (auto media = review->getMedia()) {
        if (std::find(watchedMedias.begin(), watchedMedias.end(), media) == watchedMedias.end())
            watchedMedias.push_back(media);
    }
}

void User::removeReview(const std::string& mediaTitle) {
    // Remove review do vetor
    reviews.erase(std::remove_if(reviews.begin(), reviews.end(),
        [&mediaTitle](const std::shared_ptr<Review>& r) {
            return r && r->getMediaTitle() == mediaTitle;
        }), reviews.end());

    // Atualiza watchedMedias
    watchedMedias.erase(std::remove_if(watchedMedias.begin(), watchedMedias.end(),
        [&](const std::shared_ptr<Media>& m) {
            if (!m) return true; // remove ponteiros nulos
            // remove mídia se não houver mais review associada
            auto it = std::find_if(reviews.begin(), reviews.end(),
                [&](const std::shared_ptr<Review>& r) {
                    return r && r->getMedia() == m;
                });
            return it == reviews.end();
        }), watchedMedias.end());
}

std::vector<std::shared_ptr<Review>>& User::getReviews() {
    return reviews;
}

// ----- Mídias assistidas -----
void User::addWatchedMedia(std::shared_ptr<Media> media) {
    if (!media) return;
    if (std::find(watchedMedias.begin(), watchedMedias.end(), media) == watchedMedias.end())
        watchedMedias.push_back(media);
}

size_t User::getWatchedCount() const { return watchedMedias.size(); }

std::string User::getLastReviewInfo() const {
    if (reviews.empty()) return "Nenhuma review";
    auto last = reviews.back();
    return last->getMediaTitle() + " (" + std::to_string(last->getScore()) + ")";
}

// ----- Tempo total assistido (h) -----
double User::getTotalWatchTimeHours() const {
    int totalMinutes = 0;
    for (auto& m : watchedMedias) {
        if (m) totalMinutes += m->getTotalDuration(); // Series já retorna total correto
    }

    // Arredonda para uma casa decimal
    double hours = totalMinutes / 60.0;
    return std::round(hours * 10.0) / 10.0;
}
