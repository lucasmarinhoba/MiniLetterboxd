#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Media.h"

class AppController {
private:
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Media>> medias;
    std::shared_ptr<User> loggedUser;

public:
    AppController();

    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);

    void addMovie(const std::string& title, int year, int duration);
    void addSeries(const std::string& title, int year, int episodeDuration, const std::vector<int>& episodes);

    void addReview(const std::string& mediaTitle, int score, const std::string& text, const std::string& date);
    void addFriend(const std::string& username);

    std::shared_ptr<User> getLoggedUser() const;
};
