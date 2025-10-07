#include "AppController.h"
#include "Movie.h"
#include "Series.h"
#include <iostream>
#include <algorithm>

AppController::AppController() : loggedUser(nullptr) {
    if (!persistence.loadData("", users, medias)) {
        loadDefaults();
        saveData();
    }
}

// ----- Usuário -----
bool AppController::registerUser(const std::string& username, const std::string& password, std::string& message) {
    for (const auto& u : users) {
        if (u->getUsername() == username) {
            message = "Erro: Usuário já existe!";
            return false;
        }
    }
    users.push_back(std::make_shared<User>(username, password));
    saveData();
    message = "Usuário registrado com sucesso!";
    return true;
}

bool AppController::login(const std::string& username, const std::string& password) {
    std::string msg;
    return login(username, password, msg);
}

bool AppController::login(const std::string& username, const std::string& password, std::string& message) {
    for (auto& u : users) {
        if (u->getUsername() == username && u->checkPassword(password)) {
            loggedUser = u;
            message = "Login realizado com sucesso!";
            if (onLogin) onLogin();
            return true;
        }
    }
    message = "Erro: Usuário ou senha incorretos!";
    return false;
}

void AppController::logout() {
    loggedUser = nullptr;
    if (onLogout) onLogout();
}

std::shared_ptr<User> AppController::getLoggedUser() const {
    return loggedUser;
}

// ----- Amizade -----
bool AppController::addFriend(const std::string& friendUsername, std::string& message) {
    if (!loggedUser) { message = "Nenhum usuário logado."; return false; }
    for (auto& u : users) {
        if (u->getUsername() == friendUsername) {
            loggedUser->addFriend(u);
            saveData();
            message = "Amigo adicionado com sucesso!";
            return true;
        }
    }
    message = "Usuário não encontrado!";
    return false;
}

bool AppController::deleteFriend(const std::string& friendUsername, std::string& message) {
    if (!loggedUser) { message = "Nenhum usuário logado."; return false; }
    if (loggedUser->removeFriend(friendUsername)) {
        saveData();
        message = "Amigo removido com sucesso!";
        return true;
    }
    message = "Amigo não encontrado!";
    return false;
}

// ----- Mídias -----
bool AppController::addMovie(const std::string& title, int year, int duration, std::string& message) {
    medias.push_back(std::make_shared<Movie>(title, year, duration));
    saveData();
    message = "Filme adicionado com sucesso!";
    return true;
}

// ----- ADICIONAR SÉRIE (assinatura canonical) -----
// title, year, totalEpisodes, totalSeasons, episodeDuration
bool AppController::addSeries(const std::string& title, int year, int totalEpisodes, int totalSeasons, int episodeDuration, std::string& message) {
    medias.push_back(std::make_shared<Series>(title, year, totalEpisodes, totalSeasons, episodeDuration));
    saveData();
    message = "Série adicionada com sucesso!";
    return true;
}

bool AppController::addReview(const std::string& mediaTitle, int score, const std::string& text, const std::string& date, std::string& message) {
    if (!loggedUser) { message = "Nenhum usuário logado."; return false; }

    auto it = std::find_if(medias.begin(), medias.end(),
        [&](const std::shared_ptr<Media>& m){ return m->getTitle() == mediaTitle; });
    if (it == medias.end()) { message = "Mídia não encontrada."; return false; }

    auto review = std::make_shared<Review>(*it, loggedUser, score, text, date);
    loggedUser->addReview(review);
    (*it)->addReview(review);
    saveData();

    message = "Review adicionada com sucesso!";
    return true;
}

bool AppController::deleteReview(const std::string& mediaTitle, std::string& message) {
    if (!loggedUser) { message = "Nenhum usuário logado."; return false; }

    auto& reviews = loggedUser->getReviews();
    auto it = std::remove_if(reviews.begin(), reviews.end(),
        [&](const std::shared_ptr<Review>& r){ return r && r->getMedia()->getTitle() == mediaTitle; });

    if (it != reviews.end()) {
        reviews.erase(it, reviews.end());
        for (auto& m : medias)
            if (m->getTitle() == mediaTitle)
                m->removeReviewByUser(loggedUser);

        saveData();
        message = "Review excluída com sucesso!";
        return true;
    }

    message = "Review não encontrada!";
    return false;
}

// ----- Auxiliares -----
std::vector<std::shared_ptr<Media>> AppController::getMedias() const { return medias; }

std::vector<std::string> AppController::getMediaTitles() const {
    std::vector<std::string> titles;
    for (const auto& m : medias) titles.push_back(m->getTitle());
    return titles;
}

// ----- Amizade e atividade -----
void AppController::showFriendLastActivity(const std::string& friendUsername) const {
    auto friendUser = std::find_if(users.begin(), users.end(),
        [&](const std::shared_ptr<User>& u){ return u->getUsername() == friendUsername; });

    if (friendUser == users.end()) {
        std::cout << "Amigo não encontrado.\n";
        return;
    }

    auto reviews = (*friendUser)->getReviews();
    if (reviews.empty()) {
        std::cout << friendUsername << " ainda não fez nenhuma review.\n";
        return;
    }

    std::cout << "Últimas atividades de " << friendUsername << ":\n";
    for (const auto& r : reviews) {
        std::cout << "- " << r->getMedia()->getTitle()
                  << " (" << r->getDate() << "): "
                  << r->getScore() << "/10 - " << r->getText() << "\n";
    }
}

QStringList AppController::getFriendLastActivity(const std::string& friendUsername) const {
    QStringList list;
    auto friendUser = std::find_if(users.begin(), users.end(),
        [&](const std::shared_ptr<User>& u){ return u->getUsername() == friendUsername; });

    if (friendUser == users.end()) return list;

    auto reviews = (*friendUser)->getReviews();
    for (const auto& r : reviews) {
        list.append(QString::fromStdString(r->getMedia()->getTitle() + " (" + r->getDate() + ") " +
                                           std::to_string(r->getScore()) + "/10 - " + r->getText()));
    }
    return list;
}

// ----- Mostrar reviews de mídia -----
void AppController::showUserReviewsForMedia(const std::string& mediaTitle) const {
    auto media = std::find_if(medias.begin(), medias.end(),
        [&](const std::shared_ptr<Media>& m){ return m->getTitle() == mediaTitle; });

    if (media == medias.end()) {
        std::cout << "Mídia não encontrada.\n";
        return;
    }

    auto reviews = (*media)->getReviews();
    if (reviews.empty()) {
        std::cout << "Nenhuma review para \"" << mediaTitle << "\".\n";
        return;
    }

    std::cout << "Reviews para \"" << mediaTitle << "\":\n";
    for (const auto& r : reviews) {
        if (r) {
            std::cout << "- " << r->getUser()->getUsername()
                      << ": " << r->getScore() << "/10 - "
                      << r->getText() << " (" << r->getDate() << ")\n";
        }
    }
}

// ----- Persistência -----
bool AppController::loadData() {
    bool okUsers   = persistence.loadUsers(users);
    bool okMedias  = persistence.loadMedias(medias);
    bool okReviews = persistence.loadReviews(medias, users);
    bool okFriends = persistence.loadFriends(users);
    return okUsers && okMedias && okReviews && okFriends;
}

bool AppController::saveData() {
    bool okUsers   = persistence.saveUsers(users);
    bool okMedias  = persistence.saveMedias(medias);
    bool okReviews = persistence.saveReviews(medias);
    bool okFriends = persistence.saveFriends(users);
    return okUsers && okMedias && okReviews && okFriends;
}

// ----- Defaults -----
void AppController::addDefaultUser(const std::string& username, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](const std::shared_ptr<User>& u) { return u->getUsername() == username; });

    if (it == users.end()) {
        users.push_back(std::make_shared<User>(username, password));
    }
}

void AppController::loadDefaults() {
    addDefaultUser("alice", "123");
    addDefaultUser("bob", "456");

    auto u1 = *std::find_if(users.begin(), users.end(), [](const auto& u){ return u->getUsername() == "alice"; });
    auto u2 = *std::find_if(users.begin(), users.end(), [](const auto& u){ return u->getUsername() == "bob"; });

    u1->addFriend(u2);

    auto exists = [&](const std::string& title){ return std::any_of(medias.begin(), medias.end(), [&](const auto& m){ return m->getTitle() == title; }); };

    // Filmes
    if (!exists("The Dark Knight")) medias.push_back(std::make_shared<Movie>("The Dark Knight", 2008, 152));
    if (!exists("Interstellar")) medias.push_back(std::make_shared<Movie>("Interstellar", 2014, 169));
    if (!exists("Clube da Luta")) medias.push_back(std::make_shared<Movie>("Clube da Luta", 1999, 139));
    if (!exists("Forrest Gump")) medias.push_back(std::make_shared<Movie>("Forrest Gump", 1994, 142));
    if (!exists("Um Sonho de Liberdade")) medias.push_back(std::make_shared<Movie>("Um Sonho de Liberdade", 1994, 142));
    if (!exists("Pulp Fiction")) medias.push_back(std::make_shared<Movie>("Pulp Fiction", 1994, 154));
    if (!exists("The Godfather")) medias.push_back(std::make_shared<Movie>("The Godfather", 1972, 175));
    if (!exists("The Godfather Part II")) medias.push_back(std::make_shared<Movie>("The Godfather Part II", 1974, 202));
    if (!exists("A Rede Social")) medias.push_back(std::make_shared<Movie>("A Rede Social", 2010, 120));
    if (!exists("Gladiator")) medias.push_back(std::make_shared<Movie>("Gladiator", 2000, 155));
    if (!exists("Avengers: Endgame")) medias.push_back(std::make_shared<Movie>("Avengers: Endgame", 2019, 181));
    if (!exists("The Lion King")) medias.push_back(std::make_shared<Movie>("The Lion King", 1994, 88));
    if (!exists("Toy Story")) medias.push_back(std::make_shared<Movie>("Toy Story", 1995, 81));
    if (!exists("Jurassic Park")) medias.push_back(std::make_shared<Movie>("Jurassic Park", 1993, 127));
    if (!exists("Titanic")) medias.push_back(std::make_shared<Movie>("Titanic", 1997, 195));
    if (!exists("Missao Impossivel")) medias.push_back(std::make_shared<Movie>("Missao Impossivel", 1995, 120));
    if (!exists("Orgulho e Preconceito")) medias.push_back(std::make_shared<Movie>("Orgulho e Preconceito", 2005, 120));

    // Séries (title, year, totalEpisodes, totalSeasons, episodeDuration)
    if (!exists("Game of Thrones"))
        medias.push_back(std::make_shared<Series>("Game of Thrones", 2011, 73, 8, 55));

    if (!exists("Stranger Things"))
        medias.push_back(std::make_shared<Series>("Stranger Things", 2016, 34, 4, 50));

    if (!exists("The Office"))
        medias.push_back(std::make_shared<Series>("The Office", 2005, 194, 9, 22));

    }

// ----- Auto-demo -----
void AppController::runAutoDemo() {
    std::cout << "Executando demo automática..." << std::endl;
    if (users.empty() || medias.empty()) return;

    auto demoUser = users.front();
    loggedUser = demoUser;

    std::string msg;
    addReview(medias.front()->getTitle(), 9, "Ótimo!", "01/01/2025", msg);
    addReview(medias.back()->getTitle(), 8, "Muito bom!", "02/01/2025", msg);

    loggedUser = nullptr;
}
