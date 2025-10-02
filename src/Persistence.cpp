#include "Persistence.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// ---- Salvar ----
bool Persistence::saveUsers(const std::vector<std::shared_ptr<User>>& users) {
    std::ofstream file("users.txt");
    if (!file) return false;

    for (const auto& u : users) {
        file << u->getUsername() << ";" << u->getPassword() << "\n";
    }
    return true;
}

bool Persistence::saveMedias(const std::vector<std::shared_ptr<Media>>& medias) {
    std::ofstream file("medias.txt");
    if (!file) return false;

    for (const auto& m : medias) {
        file << m->getTitle() << ";" << m->getType() << ";"
             << m->getYear() << ";" << m->getTotalDuration() << "\n";
    }
    return true;
}

bool Persistence::saveReviews(const std::vector<std::shared_ptr<Media>>& medias) {
    std::ofstream file("reviews.txt");
    if (!file) return false;

    for (const auto& m : medias) {
        for (const auto& r : m->getReviews()) {
            auto user = r->getUser();
            file << m->getTitle() << ";" << user->getUsername() << ";"
                 << r->getScore() << ";" << r->getText() << ";" << r->getDate() << "\n";
        }
    }
    return true;
}

// ---- Carregar ----
bool Persistence::loadUsers(std::vector<std::shared_ptr<User>>& users) {
    std::ifstream file("users.txt");
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        auto sep = line.find(';');
        if (sep != std::string::npos) {
            std::string username = line.substr(0, sep);
            std::string password = line.substr(sep + 1);
            users.push_back(std::make_shared<User>(username, password));
        }
    }
    return true;
}

bool Persistence::loadMedias(std::vector<std::shared_ptr<Media>>& medias) {
    std::ifstream file("medias.txt");
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        auto t1 = line.find(';');
        auto t2 = line.find(';', t1 + 1);
        auto t3 = line.find(';', t2 + 1);
        if (t1 != std::string::npos && t2 != std::string::npos && t3 != std::string::npos) {
            std::string title = line.substr(0, t1);
            std::string type = line.substr(t1 + 1, t2 - t1 - 1);
            int year = std::stoi(line.substr(t2 + 1, t3 - t2 - 1));
            int duration = std::stoi(line.substr(t3 + 1));

            if (type == "Movie")
                medias.push_back(std::make_shared<Movie>(title, year, duration));
            else if (type == "Series")
                medias.push_back(std::make_shared<Series>(title, year, duration)); // duração por episódio
        }
    }
    return true;
}

bool Persistence::loadReviews(std::vector<std::shared_ptr<Media>>& medias,
                              std::vector<std::shared_ptr<User>>& users) {
    std::ifstream file("reviews.txt");
    if (!file) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos ||
            pos3 == std::string::npos || pos4 == std::string::npos) continue;

        std::string title = line.substr(0, pos1);
        std::string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        int score = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        std::string text = line.substr(pos3 + 1, pos4 - pos3 - 1);
        std::string date = line.substr(pos4 + 1);

        // Encontrar a mídia correspondente
        auto it_media = std::find_if(medias.begin(), medias.end(),
            [&](const std::shared_ptr<Media>& m){ return m->getTitle() == title; });

        if (it_media != medias.end()) {
            // Encontrar o usuário correspondente
            auto it_user = std::find_if(users.begin(), users.end(),
                [&](const std::shared_ptr<User>& u){ return u->getUsername() == username; });

            if (it_user != users.end()) {
                auto review = std::make_shared<Review>(*it_media, *it_user, score, text, date);
                (*it_media)->addReview(review);
                (*it_user)->addReview(review);
            } else {
                std::cerr << "Aviso: usuário '" << username << "' não encontrado para review de '" << title << "'\n";
            }
        }
    }
    return true;
}

// ---- Métodos unificados ----
bool Persistence::saveData(const std::string& filename,
                           const std::vector<std::shared_ptr<User>>& users,
                           const std::vector<std::shared_ptr<Media>>& medias) {
    return saveUsers(users) && saveMedias(medias) && saveReviews(medias);
}

bool Persistence::loadData(const std::string& filename,
                           std::vector<std::shared_ptr<User>>& users,
                           std::vector<std::shared_ptr<Media>>& medias) {
    return loadUsers(users) && loadMedias(medias) && loadReviews(medias, users);
}
