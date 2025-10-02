#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Review.h"
#include "Media.h"

class User {
private:
    std::string username;
    std::string password;
    std::vector<std::shared_ptr<Review>> reviews;
    std::vector<std::weak_ptr<User>> friends;
    std::vector<std::shared_ptr<Media>> watchedMedias; // Mídias assistidas

public:
    User(const std::string& username, const std::string& password);

    // Getters básicos
    std::string getUsername() const;
    std::string getPassword() const; // necessário para persistência
    bool checkPassword(const std::string& pass) const;

    // Amigos
    void addFriend(std::shared_ptr<User> user);
    std::vector<std::weak_ptr<User>> getFriends() const;

    // Reviews
    void addReview(std::shared_ptr<Review> review);
    void removeReview(const std::string& mediaTitle);
    std::vector<std::shared_ptr<Review>> getReviews() const;

    // Mídias assistidas
    void addWatchedMedia(std::shared_ptr<Media> media);
    size_t getWatchedCount() const;
    std::string getLastReviewInfo() const;
    double getTotalWatchTimeHours() const;
};
