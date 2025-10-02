#pragma once
#include <string>
#include <memory>
#include <vector>
#include "User.h"
#include "Media.h"
#include "Review.h"

/**
 * @brief Classe base para a interface de usuário (GUI ou CLI).
 * Define as operações que uma view deve oferecer para interação com o usuário.
 */
class GUIView {
public:
    virtual ~GUIView() = default;

    // ---- Métodos de login e usuário ----
    virtual void showLoginScreen() = 0;
    virtual void showUserPage(const User& user) = 0;
    virtual void showFriends(const std::vector<std::shared_ptr<User>>& friends) = 0;

    // ---- Métodos para mídia ----
    virtual void showMediaList(const std::vector<std::shared_ptr<Media>>& mediaList) = 0;
    virtual void showMediaDetails(const std::shared_ptr<Media>& media) = 0;

    // ---- Métodos para reviews ----
    virtual void showReviews(const std::vector<std::shared_ptr<Review>>& reviews) = 0;
    virtual void showAddReviewForm(const std::shared_ptr<Media>& media) = 0;

    // ---- Mensagens gerais ----
    virtual void showMessage(const std::string& msg) = 0;
    virtual void showError(const std::string& err) = 0;
};
