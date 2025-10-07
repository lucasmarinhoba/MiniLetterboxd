#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <QStringList>
#include "User.h"
#include "Media.h"
#include "Persistence.h"
#include "Review.h"

class AppController {
public:
    AppController();

    // Callbacks para a GUI
    std::function<void()> onLogin;
    std::function<void()> onLogout;

    // ----- Usuário -----
    bool registerUser(const std::string& username, const std::string& password, std::string& message);
    bool login(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password, std::string& message);
    void logout();
    std::shared_ptr<User> getLoggedUser() const;

    // ----- Amizade -----
    bool addFriend(const std::string& friendUsername, std::string& message);
    bool deleteFriend(const std::string& friendUsername, std::string& message);

    // ----- Mídias -----
    bool addMovie(const std::string& title, int year, int duration, std::string& message);

    // Assinatura canonical para adicionar série:
    // title, year, totalEpisodes, totalSeasons, episodeDuration, message
    bool addSeries(const std::string& title, int year, int totalEpisodes, int totalSeasons, int episodeDuration, std::string& message);

    bool addReview(const std::string& mediaTitle, int score, const std::string& text, const std::string& date, std::string& message);
    bool deleteReview(const std::string& mediaTitle, std::string& message);

    std::vector<std::shared_ptr<Media>> getMedias() const;
    std::vector<std::string> getMediaTitles() const;

    // ----- Amizade e atividade -----
    void showFriendLastActivity(const std::string& friendUsername) const; // CLI
    QStringList getFriendLastActivity(const std::string& friendUsername) const; // GUI
    void showUserReviewsForMedia(const std::string& mediaTitle) const;

    // ----- Persistência -----
    bool loadData();
    bool saveData();

    // ----- Defaults -----
    void loadDefaults();
    void addDefaultUser(const std::string& username, const std::string& password);

    // ----- Auto-demo -----
    void runAutoDemo();

    // ----- Info usuário logado -----
    void showLoggedUserInfo() const;

private:
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Media>> medias;
    std::shared_ptr<User> loggedUser;

    Persistence persistence;

    // Métodos internos
    void updateLoggedUserInfo() const;
};
