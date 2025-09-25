#pragma once
#include <string>
#include <vector>
#include <memory>
#include "User.h"
#include "Media.h"

class Persistence {
public:
    static void saveData(const std::string& filename,
                         const std::vector<std::shared_ptr<User>>& users,
                         const std::vector<std::shared_ptr<Media>>& medias);

    static void loadData(const std::string& filename,
                         std::vector<std::shared_ptr<User>>& users,
                         std::vector<std::shared_ptr<Media>>& medias);
};
