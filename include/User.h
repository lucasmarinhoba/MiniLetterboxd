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

public:
    User(const std::string& username, const std::string& password);

    std::string getUsername() const;
    bool checkPassword(const std::string& pass) const;

    void addFriend(std::shared_ptr<User> user);
    std::vector<std::weak_ptr<User>> getFriends() const;

    void addReview(std::shared_ptr<Review> review);
    void removeReview(const std::string& mediaTitle);
    std::vector<std::shared_ptr<Review>> getReviews() const;

    size_t getWatchedCount() const;
    std::string getLastReviewInfo() const;
    double getTotalWatchTimeHours() const;
};
