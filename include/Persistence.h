#pragma once
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include "User.h"
#include "Media.h"
#include "Movie.h"
#include "Series.h"
#include "Review.h"

/**
 * @brief Classe responsável por salvar e carregar dados do sistema.
 * Cria automaticamente a pasta "data/" na raiz do projeto, garantindo portabilidade.
 */
class Persistence {
private:
    std::filesystem::path dataDir;
    std::filesystem::path usersFile;
    std::filesystem::path mediasFile;
    std::filesystem::path reviewsFile;
    std::filesystem::path friendsFile;

public:
    Persistence();

    // ---- Salvar ----
    bool saveUsers(const std::vector<std::shared_ptr<User>>& users);
    bool saveMedias(const std::vector<std::shared_ptr<Media>>& medias);
    bool saveReviews(const std::vector<std::shared_ptr<Media>>& medias);
    bool saveFriends(const std::vector<std::shared_ptr<User>>& users);

    // ---- Carregar ----
    bool loadUsers(std::vector<std::shared_ptr<User>>& users);
    bool loadMedias(std::vector<std::shared_ptr<Media>>& medias);
    bool loadReviews(std::vector<std::shared_ptr<Media>>& medias,
                     std::vector<std::shared_ptr<User>>& users);
    bool loadFriends(std::vector<std::shared_ptr<User>>& users);

    // ---- Métodos unificados (para AppController) ----
    bool saveData(const std::string& filename,
                  const std::vector<std::shared_ptr<User>>& users,
                  const std::vector<std::shared_ptr<Media>>& medias);

    bool loadData(const std::string& filename,
                  std::vector<std::shared_ptr<User>>& users,
                  std::vector<std::shared_ptr<Media>>& medias);
};
