#include "AppController.h"
#include "Movie.h"
#include "Series.h"
#include <iostream>
#include <algorithm>

AppController::AppController() : loggedUser(nullptr) {}

// ----- Usuário -----
bool AppController::registerUser(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            std::cout << "Erro: Usuário já existe!\n";
            return false;
        }
    }

    auto newUser = std::make_shared<User>(username, password);
    users.push_back(newUser);
    std::cout << "Usuário registrado com sucesso!\n";
    return true;
}

bool AppController::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user->getUsername() == username && user->checkPassword(password)) {
            loggedUser = user;
            std::cout << "Login realizado com sucesso! Bem-vindo, " << username << "!\n";
            return true;
        }
    }
    std::cout << "Erro: Usuário ou senha incorretos!\n";
    return false;
}

void AppController::addFriend(const std::string& username) {
    if (!loggedUser) {
        std::cout << "Erro: Nenhum usuário logado!\n";
        return;
    }

    for (auto& user : users) {
        if (user->getUsername() == username) {
            loggedUser->addFriend(user);
            std::cout << "Amigo adicionado com sucesso!\n";
            return;
        }
    }
    std::cout << "Erro: Usuário não encontrado!\n";
}

std::shared_ptr<User> AppController::getLoggedUser() const {
    return loggedUser;
}

// ----- Mídias -----
void AppController::addMovie(const std::string& title, int year, int duration) {
    auto movie = std::make_shared<Movie>(title, year, duration);
    medias.push_back(movie);
    std::cout << "Filme adicionado com sucesso!\n";
}

void AppController::addSeries(const std::string& title, int year, int episodeDuration, const std::vector<int>& episodes) {
    auto series = std::make_shared<Series>(title, year, episodeDuration, episodes);
    medias.push_back(series);
    std::cout << "Série adicionada com sucesso!\n";
}

void AppController::addReview(const std::string& mediaTitle, int score, const std::string& text, const std::string& date) {
    if (!loggedUser) {
        std::cout << "Erro: Nenhum usuário logado!\n";
        return;
    }

    std::shared_ptr<Media> foundMedia = nullptr;
    for (auto& media : medias) {
        if (media->getTitle() == mediaTitle) {
            foundMedia = media;
            break;
        }
    }

    if (!foundMedia) {
        std::cout << "Erro: Mídia não encontrada!\n";
        return;
    }

    auto review = std::make_shared<Review>(foundMedia, loggedUser, score, text, date);
    loggedUser->addReview(review);
    foundMedia->addReview(review);

    std::cout << "Review adicionada com sucesso!\n";
}

// Getter para CLIView
std::vector<std::shared_ptr<Media>> AppController::getMedias() const {
    return medias;
}

// ----- Persistência -----
bool AppController::loadData() {
    return Persistence::loadData("data.txt", users, medias);
}

bool AppController::saveData() {
    return Persistence::saveData("data.txt", users, medias);
}

// ----- Dados padrão -----
void AppController::addDefaultUser(const std::string& username, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](const std::shared_ptr<User>& u){ return u->getUsername() == username; });
    if (it == users.end()) {
        users.push_back(std::make_shared<User>(username, password));
    }
}

void AppController::loadDefaults() {
    addDefaultUser("alice", "123");
    addDefaultUser("bob", "456");

    auto user1 = *std::find_if(users.begin(), users.end(),
        [](const std::shared_ptr<User>& u){ return u->getUsername() == "alice"; });
    auto user2 = *std::find_if(users.begin(), users.end(),
        [](const std::shared_ptr<User>& u){ return u->getUsername() == "bob"; });

    user1->addFriend(user2);

    auto movieExists = [&](const std::string& title){
        return std::any_of(medias.begin(), medias.end(), [&](const auto& m){ return m->getTitle() == title; });
    };

    if (!movieExists("Inception")) medias.push_back(std::make_shared<Movie>("Inception", 2010, 148));
    if (!movieExists("The Matrix")) medias.push_back(std::make_shared<Movie>("The Matrix", 1999, 136));
    if (!movieExists("Breaking Bad")) medias.push_back(std::make_shared<Series>("Breaking Bad", 2008, 47, std::vector<int>{7,13,13,13,16}));
}

// ----- Auto-Demo -----
void AppController::runAutoDemo() {
    std::cout << "\n========== AUTO-DEMO ==========\n";

    loadDefaults(); // não limpa dados existentes

    std::cout << "\n--- Usuários cadastrados ---\n";
    for (const auto& user : users) {
        std::cout << "- " << user->getUsername() << "\n";
    }

    std::cout << "\n--- Mídias cadastradas ---\n";
    for (const auto& media : medias) {
        std::cout << "- " << media->getTitle()
                  << " (" << media->getType() << ")"
                  << " - Média: " << media->getAverageScore() << "\n";
    }

    login("alice", "123");

    std::cout << "\n--- Informações do usuário ---\n";
    showLoggedUserInfo();

    std::cout << "\n========== FIM DO AUTO-DEMO ==========\n";
}

// ----- Info usuário logado -----
void AppController::showLoggedUserInfo() const {
    if (!loggedUser) {
        std::cout << "Nenhum usuário logado.\n";
        return;
    }

    std::cout << "Usuário: " << loggedUser->getUsername() << "\n";
    std::cout << "Mídias assistidas: " << loggedUser->getWatchedCount() << "\n";
    std::cout << "Tempo total (h): " << loggedUser->getTotalWatchTimeHours() << "\n";
    std::cout << "Última review: " << loggedUser->getLastReviewInfo() << "\n";
}
