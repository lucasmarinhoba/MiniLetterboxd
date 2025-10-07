#include "CLIView.h"
#include "AppController.h"
#include "User.h"
#include "Series.h" // necessário para o dynamic_cast
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <vector>

CLIView::CLIView(AppController& ctrl) : controller(ctrl) {}

void CLIView::pause() {
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CLIView::showMainMenu() {
    int option = 0;
    do {
        std::cout << "\n===== Mini Letterboxd (CLI) =====\n";
        std::cout << "1. Registrar usuário\n2. Login\n0. Sair\nEscolha: ";
        std::cin >> option;

        if(std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            option = -1; 
        }

        std::string msg;
        switch(option) {
            case 1: {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                controller.registerUser(user, pass, msg);
                std::cout << msg << "\n";
                pause();
                break;
            }
            case 2: {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                if(controller.login(user, pass, msg)) { 
                    std::cout << msg << "\n"; 
                    pause(); 
                    showUserMenu(); 
                } else { 
                    std::cout << msg << "\n"; 
                    pause(); 
                }
                break;
            }
            case 0: std::cout << "Saindo...\n"; break;
            default: std::cout << "Opção inválida.\n"; pause();
        }
    } while(option != 0);
}

void CLIView::showUserMenu() {
    auto user = controller.getLoggedUser();
    if(!user) return;

    int option = 0;
    do {
        std::cout << "\n===== Mini Letterboxd (Usuário: " << user->getUsername() << ") =====\n";
        std::cout << "1. Adicionar filme\n2. Adicionar série\n3. Adicionar review\n4. Excluir review\n";
        std::cout << "5. Adicionar amigo\n6. Excluir amigo\n7. Listar amigos\n8. Listar mídias com reviews\n";
        std::cout << "9. Ver última atividade de amigo\n10. Ver minha página\n0. Logout\nEscolha: ";
        std::cin >> option;

        if(std::cin.fail()) { 
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            option = -1; 
        }

        std::string msg;
        switch(option) {
            case 1: {
                std::string title; int year, duration;
                std::cout << "Título: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Ano: "; std::cin >> year;
                std::cout << "Duração (min): "; std::cin >> duration;
                controller.addMovie(title, year, duration, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 2: {
                std::string title; int year, epDuration, seasons;
                std::cout << "Título: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Ano: "; std::cin >> year;
                std::cout << "Duração de cada episódio (min): "; std::cin >> epDuration;
                std::cout << "Número de temporadas: "; std::cin >> seasons;

                std::vector<int> episodes(seasons);
                int totalEpisodes = 0;
                for(int i=0; i<seasons; i++) {
                    std::cout << "Episódios da temporada " << i+1 << ": "; std::cin >> episodes[i];
                    totalEpisodes += episodes[i];
                }

                controller.addSeries(title, year, totalEpisodes, seasons, epDuration, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 3: {
                std::string title, text, date; int score;
                std::cout << "Título da mídia: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Nota (0-10): "; std::cin >> score;
                std::cin.ignore(); 
                std::cout << "Review: "; std::getline(std::cin, text);
                std::cout << "Data (DD/MM/AAAA): "; std::getline(std::cin, date);

                controller.addReview(title, score, text, date, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 4: {
                std::string title; std::cin.ignore();
                std::cout << "Título da review a excluir: "; std::getline(std::cin, title);
                controller.deleteReview(title, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 5: {
                std::string friendUser; std::cin >> friendUser;
                controller.addFriend(friendUser, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 6: {
                std::string friendUser; std::cin >> friendUser;
                controller.deleteFriend(friendUser, msg);
                std::cout << msg << "\n";
                controller.saveData();
                pause();
                break;
            }
            case 7: listFriends(user); pause(); break;
            case 8: listMedias(); pause(); break;
            case 9: {
                std::string friendUser; std::cin >> friendUser;
                controller.showFriendLastActivity(friendUser);
                pause();
                break;
            }
            case 10: showUserPage(); pause(); break;
            case 0: controller.logout(); std::cout << "Logout realizado.\n"; pause(); break;
            default: std::cout << "Opção inválida.\n"; pause();
        }

    } while(option != 0);
}

void CLIView::listMedias() {
    auto medias = controller.getMedias();
    if(medias.empty()) { 
        std::cout << "Nenhuma mídia cadastrada.\n"; 
        return; 
    }

    std::cout << "\n--- Lista de mídias ---\n";
    int i = 1;
    for(auto& m : medias) {
        std::cout << i++ << ". " << m->getTitle() << " (" << m->getType() << ") - Ano: " << m->getYear();

        if(m->getType() == "Filme") {
            std::cout << " - Duração: " << m->getDuration() << " min";
        } else if(m->getType() == "Série") {
            Series* s = dynamic_cast<Series*>(m.get());
            if(s) {
                std::cout << " - Duração de um episódio: " << s->getEpisodeDuration() << " min"
                          << " - Total de episódios: " << s->getTotalEpisodes()
                          << " - Temporadas: " << s->getTotalSeasons();
            }
        }

        std::cout << " - Média: " << m->getAverageScore() << "\n";
        controller.showUserReviewsForMedia(m->getTitle());
    }
}

void CLIView::showUserPage() {
    auto user = controller.getLoggedUser();
    if(!user) { std::cout << "Nenhum usuário logado.\n"; return; }

    std::cout << "\n=== Página de " << user->getUsername() << " ===\n";
    std::cout << "Filmes/Séries assistidos: " << user->getWatchedCount() << "\n";
    std::cout << "Tempo total assistido (h): " << user->getTotalWatchTimeHours() << "\n";
    std::cout << "Última review: " << user->getLastReviewInfo() << "\n";
}

void CLIView::listFriends(std::shared_ptr<User> user) {
    auto friends = user->getFriends();
    if(friends.empty()) { 
        std::cout << "\nVocê ainda não tem amigos adicionados.\n"; 
        return; 
    }

    std::cout << "\n=== Amigos de " << user->getUsername() << " ===\n";
    for(const auto& f : friends) {
        if(auto sp = f.lock()) { 
            std::cout << "- " << sp->getUsername() << "\n"; 
        }
    }
}

void CLIView::runAutoDemo() {
    controller.runAutoDemo();
    controller.saveData();
}
