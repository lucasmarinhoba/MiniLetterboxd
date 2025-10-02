#pragma once
#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Media.h"
#include "Movie.h"
#include "Series.h"
#include "Review.h"

class Persistence {
public:
    // ---- Salvar ----
    static bool saveUsers(const std::vector<std::shared_ptr<User>>& users);
    static bool saveMedias(const std::vector<std::shared_ptr<Media>>& medias);
    static bool saveReviews(const std::vector<std::shared_ptr<Media>>& medias);

    // ---- Carregar ----
    static bool loadUsers(std::vector<std::shared_ptr<User>>& users);
    static bool loadMedias(std::vector<std::shared_ptr<Media>>& medias);
    static bool loadReviews(std::vector<std::shared_ptr<Media>>& medias,
                            std::vector<std::shared_ptr<User>>& users);

    // ---- Métodos unificados (para AppController) ----
    static bool saveData(const std::string& filename,
                         const std::vector<std::shared_ptr<User>>& users,
                         const std::vector<std::shared_ptr<Media>>& medias);

    static bool loadData(const std::string& filename,
                         std::vector<std::shared_ptr<User>>& users,
                         std::vector<std::shared_ptr<Media>>& medias);
};
