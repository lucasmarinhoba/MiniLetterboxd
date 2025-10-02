#include "Review.h"
#include "Media.h"
#include "User.h"
#include <stdexcept>

// Construtor principal (Media + User + Score + Texto + Data)
Review::Review(const std::shared_ptr<Media>& m,
               const std::shared_ptr<User>& u,
               int s,
               const std::string& t,
               const std::string& d)
    : media(m), user(u), score(s), text(t), date(d) {

    if (!m) throw std::invalid_argument("Media não pode ser nula");
    if (!u) throw std::invalid_argument("Review deve ter um User associado");
    if (s < 0 || s > 10) throw std::invalid_argument("Score deve estar entre 0 e 10");
}

// Getters
std::string Review::getMediaTitle() const {
    return media ? media->getTitle() : "N/A";
}

int Review::getScore() const { return score; }
std::string Review::getText() const { return text; }
std::string Review::getDate() const { return date; }
std::shared_ptr<User> Review::getUser() const { return user; }

// Setter e getter para Media
void Review::setMedia(const std::shared_ptr<Media>& m) {
    if (!m) throw std::invalid_argument("Media não pode ser nula");
    media = m;
}

std::shared_ptr<Media> Review::getMedia() const { return media; }
