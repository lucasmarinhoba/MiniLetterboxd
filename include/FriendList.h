#pragma once
#include <vector>
#include <memory>
#include "User.h"

class FriendList {
private:
    std::vector<std::weak_ptr<User>> friends;

public:
    void addFriend(std::shared_ptr<User> user);
    std::vector<std::weak_ptr<User>> getFriends() const;
};
