#pragma once
#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Media.h"
#include "Persistence.h"
#include "Review.h"

class AppController {
public:
    AppController();

    // ----- Usuário -----
    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void addFriend(const std::string& username);
    std::shared_ptr<User> getLoggedUser() const;

    // ----- Mídias -----
    void addMovie(const std::string& title, int year, int duration);
    void addSeries(const std::string& title, int year, int episodeDuration, const std::vector<int>& episodes);
    void addReview(const std::string& mediaTitle, int score, const std::string& text, const std::string& date);
    std::vector<std::shared_ptr<Media>> getMedias() const; // getter para CLIView

    // ----- Persistência -----
    bool loadData();
    bool saveData();

    // ----- Dados padrão -----
    void loadDefaults();

    // ----- Auto-Demo -----
    void runAutoDemo();

    // ----- Mostrar info usuário logado -----
    void showLoggedUserInfo() const;

private:
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Media>> medias;
    std::shared_ptr<User> loggedUser;

    void addDefaultUser(const std::string& username, const std::string& password); // helper
};
