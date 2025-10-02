#pragma once
#include <string>
#include <memory>

// Forward declaration
class Media;
class User;

class Review {
private:
    std::shared_ptr<Media> media;
    std::shared_ptr<User> user; // agora obrigatoriamente não nulo
    int score;
    std::string text;
    std::string date;

public:
    // Construtor principal (Media + User + Score + Texto + Data)
    Review(const std::shared_ptr<Media>& m,
           const std::shared_ptr<User>& u,
           int s,
           const std::string& t,
           const std::string& d);

    // Getters
    std::string getMediaTitle() const;
    int getScore() const;
    std::string getText() const;
    std::string getDate() const;
    std::shared_ptr<User> getUser() const;

    // Setter e getter para Media
    void setMedia(const std::shared_ptr<Media>& m);
    std::shared_ptr<Media> getMedia() const;
};
