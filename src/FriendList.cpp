#include ".h"

// Adiciona um amigo à lista
void FriendList::addFriend(const std::shared_ptr<User>& user) {
    // Evita adicionar nullptr ou amigo duplicado
    if (!user) return;

    for (const auto& f : friends) {
        if (auto sp = f.lock()) {  // Converte weak_ptr para shared_ptr temporário
            if (sp == user) return; // Já está na lista
        }
    }

    friends.push_back(user);
}

// Retorna a lista de amigos
std::vector<std::weak_ptr<User>> FriendList::getFriends() const {
    return friends;
}
