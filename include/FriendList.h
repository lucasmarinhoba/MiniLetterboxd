#pragma once
#include <vector>
#include <memory>
#include "User.h"

class FriendList {
private:
    std::vector<std::weak_ptr<User>> friends; // Armazena amigos como weak_ptr para evitar ciclos

public:
    // Adiciona um amigo à lista
    void addFriend(const std::shared_ptr<User>& user);

    // Retorna a lista de amigos
    std::vector<std::weak_ptr<User>> getFriends() const;
};
