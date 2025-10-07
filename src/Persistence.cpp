#include "Persistence.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

Persistence::Persistence() {
    fs::path execDir = fs::current_path();

    // Se o executável estiver sendo rodado dentro de "build/", volta para a raiz
    if (execDir.filename() == "build") {
        execDir = execDir.parent_path();
    }

    // Cria ou usa a pasta "data" na raiz do projeto
    dataDir = execDir / "data";
    if (!fs::exists(dataDir)) {
        fs::create_directories(dataDir);
        std::cout << "[INFO] Pasta 'data' criada em: " << dataDir << std::endl;
    }

    usersFile   = dataDir / "users.txt";
    mediasFile  = dataDir / "medias.txt";
    reviewsFile = dataDir / "reviews.txt";
    friendsFile = dataDir / "friends.txt";
}

// ---- Salvar ----
bool Persistence::saveUsers(const std::vector<std::shared_ptr<User>>& users) {
    std::ofstream file(usersFile);
    if (!file) return false;

    for (const auto& u : users)
        file << u->getUsername() << ";" << u->getPassword() << "\n";

    return true;
}

bool Persistence::saveMedias(const std::vector<std::shared_ptr<Media>>& medias) {
    std::ofstream file(mediasFile);
    if (!file) return false;

    for (const auto& m : medias) {
        if (m->isSeries()) {
            auto s = std::dynamic_pointer_cast<Series>(m);
            file << s->getTitle() << ";Series;" << s->getYear() << ";"
                 << s->getTotalEpisodes() << ";" << s->getTotalSeasons() << ";" << s->getEpisodeDuration() << "\n";
        } else { // Movie
            auto mv = std::dynamic_pointer_cast<Movie>(m);
            file << mv->getTitle() << ";Movie;" << mv->getYear() << ";" << mv->getTotalDuration() << "\n";
        }
    }
    return true;
}

bool Persistence::saveReviews(const std::vector<std::shared_ptr<Media>>& medias) {
    std::ofstream file(reviewsFile);
    if (!file) return false;

    for (const auto& m : medias) {
        for (const auto& r : m->getReviews()) {
            auto user = r->getUser();
            if (user) {
                file << m->getTitle() << ";" << user->getUsername() << ";"
                     << r->getScore() << ";" << r->getText() << ";" << r->getDate() << "\n";
            }
        }
    }
    return true;
}

bool Persistence::saveFriends(const std::vector<std::shared_ptr<User>>& users) {
    std::ofstream file(friendsFile);
    if (!file) return false;

    for (const auto& u : users) {
        for (const auto& f : u->getFriends()) {
            if (auto fptr = f.lock()) {
                file << u->getUsername() << ";" << fptr->getUsername() << "\n";
            }
        }
    }
    return true;
}

// ---- Carregar ----
bool Persistence::loadUsers(std::vector<std::shared_ptr<User>>& users) {
    std::ifstream file(usersFile);
    if (!file) {
        std::cerr << "[AVISO] Arquivo de usuários não encontrado em: " << usersFile << std::endl;
        return false;
    }

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
    std::ifstream file(mediasFile);
    if (!file) {
        std::cerr << "[AVISO] Arquivo de mídias não encontrado em: " << mediasFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        auto t1 = line.find(';');
        auto t2 = line.find(';', t1 + 1);
        auto t3 = line.find(';', t2 + 1);

        if (t1 != std::string::npos && t2 != std::string::npos && t3 != std::string::npos) {
            std::string title = line.substr(0, t1);
            std::string type = line.substr(t1 + 1, t2 - t1 - 1);
            int year = std::stoi(line.substr(t2 + 1, t3 - t2 - 1));

            if (type == "Movie") {
                int duration = std::stoi(line.substr(t3 + 1));
                medias.push_back(std::make_shared<Movie>(title, year, duration));
            } else if (type == "Series") {
                auto t4 = line.find(';', t3 + 1);
                auto t5 = line.find(';', t4 + 1);
                if (t4 != std::string::npos && t5 != std::string::npos) {
                    int totalEpisodes = std::stoi(line.substr(t3 + 1, t4 - t3 - 1));
                    int totalSeasons = std::stoi(line.substr(t4 + 1, t5 - t4 - 1));
                    int episodeDuration = std::stoi(line.substr(t5 + 1));
                    medias.push_back(std::make_shared<Series>(title, year, totalEpisodes, totalSeasons, episodeDuration));
                }
            }
        }
    }
    return true;
}

bool Persistence::loadReviews(std::vector<std::shared_ptr<Media>>& medias,
                              std::vector<std::shared_ptr<User>>& users) {
    std::ifstream file(reviewsFile);
    if (!file) {
        std::cerr << "[AVISO] Arquivo de reviews não encontrado em: " << reviewsFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);
        if (pos1 == std::string::npos || pos2 == std::string::npos ||
            pos3 == std::string::npos || pos4 == std::string::npos)
            continue;

        std::string title = line.substr(0, pos1);
        std::string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        int score = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        std::string text = line.substr(pos3 + 1, pos4 - pos3 - 1);
        std::string date = line.substr(pos4 + 1);

        auto it_media = std::find_if(medias.begin(), medias.end(),
            [&](const std::shared_ptr<Media>& m){ return m->getTitle() == title; });

        if (it_media != medias.end()) {
            auto it_user = std::find_if(users.begin(), users.end(),
                [&](const std::shared_ptr<User>& u){ return u->getUsername() == username; });

            if (it_user != users.end()) {
                auto review = std::make_shared<Review>(*it_media, *it_user, score, text, date);
                (*it_media)->addReview(review);
                (*it_user)->addReview(review);
            } else {
                std::cerr << "Aviso: usuário '" << username
                          << "' não encontrado para review de '" << title << "'\n";
            }
        }
    }
    return true;
}

bool Persistence::loadFriends(std::vector<std::shared_ptr<User>>& users) {
    std::ifstream file(friendsFile);
    if (!file) {
        std::cerr << "[AVISO] Arquivo de amizades não encontrado em: " << friendsFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find(';');
        if (pos == std::string::npos) continue;

        std::string u1 = line.substr(0, pos);
        std::string u2 = line.substr(pos + 1);

        auto it1 = std::find_if(users.begin(), users.end(),
            [&](const std::shared_ptr<User>& u){ return u->getUsername() == u1; });
        auto it2 = std::find_if(users.begin(), users.end(),
            [&](const std::shared_ptr<User>& u){ return u->getUsername() == u2; });

        if (it1 != users.end() && it2 != users.end()) {
            (*it1)->addFriend(*it2);
        }
    }
    return true;
}

// ---- Métodos unificados ----
bool Persistence::saveData(const std::string&,
                           const std::vector<std::shared_ptr<User>>& users,
                           const std::vector<std::shared_ptr<Media>>& medias) {
    return saveUsers(users) && saveMedias(medias) && saveReviews(medias) && saveFriends(users);
}

bool Persistence::loadData(const std::string&,
                           std::vector<std::shared_ptr<User>>& users,
                           std::vector<std::shared_ptr<Media>>& medias) {
    return loadUsers(users) && loadMedias(medias) && loadReviews(medias, users) && loadFriends(users);
}
