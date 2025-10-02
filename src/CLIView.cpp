#include "CLIView.h"
#include "AppController.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

CLIView::CLIView(AppController& ctrl) : controller(ctrl) {}

// Menu principal
void CLIView::showMainMenu() {
    int option = 0;
    do {
        std::cout << "\n===== Mini Letterboxd (CLI) =====\n";
        std::cout << "1. Registrar usuário\n";
        std::cout << "2. Login\n";
        std::cout << "3. Adicionar filme\n";
        std::cout << "4. Adicionar série\n";
        std::cout << "5. Adicionar review\n";
        std::cout << "6. Adicionar amigo\n";
        std::cout << "7. Listar mídias\n";
        std::cout << "8. Ver página do usuário\n";
        std::cout << "9. Auto-Demo\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha: ";
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            option = -1;
        }

        switch (option) {
            case 1: {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                if (controller.registerUser(user, pass))
                    std::cout << "Usuário registrado com sucesso!\n";
                else
                    std::cout << "Erro: usuário já existe.\n";
                break;
            }
            case 2: {
                std::string user, pass;
                std::cout << "Username: "; std::cin >> user;
                std::cout << "Password: "; std::cin >> pass;
                if (controller.login(user, pass))
                    std::cout << "Login realizado com sucesso!\n";
                else
                    std::cout << "Erro: usuário ou senha incorretos.\n";
                break;
            }
            case 3: {
                std::string title; int year, duration;
                std::cout << "Título: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Ano: "; std::cin >> year;
                std::cout << "Duração (min): "; std::cin >> duration;
                controller.addMovie(title, year, duration);
                break;
            }
            case 4: {
                std::string title; int year, epDuration, seasons;
                std::cout << "Título: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Ano: "; std::cin >> year;
                std::cout << "Duração de cada episódio (min): "; std::cin >> epDuration;
                std::cout << "Número de temporadas: "; std::cin >> seasons;
                std::vector<int> episodes(seasons);
                for (int i = 0; i < seasons; i++) {
                    std::cout << "Episódios da temporada " << i+1 << ": ";
                    std::cin >> episodes[i];
                }
                controller.addSeries(title, year, epDuration, episodes);
                break;
            }
            case 5: {
                std::string title, text, date; int score;
                std::cout << "Título da mídia: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Nota (0-10): "; std::cin >> score;
                std::cout << "Review: "; std::cin.ignore(); std::getline(std::cin, text);
                std::cout << "Data (DD/MM/AAAA): "; std::getline(std::cin, date);
                controller.addReview(title, score, text, date);
                break;
            }
            case 6: {
                std::string friendUser;
                std::cout << "Nome do amigo: "; std::cin >> friendUser;
                controller.addFriend(friendUser);
                break;
            }
            case 7:
                listMedias();
                break;
            case 8:
                showUserPage();
                break;
            case 9:
                runAutoDemo();
                break;
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida.\n";
        }

    } while (option != 0);
}

void CLIView::listMedias() {
    auto medias = controller.getMedias();
    if (medias.empty()) { 
        std::cout << "Nenhuma mídia cadastrada.\n"; 
        return; 
    }

    std::cout << "\n--- Lista de mídias ---\n";
    int i = 1;
    for (auto& m : medias) {
        std::cout << i++ << ". " << m->getTitle() 
                  << " (" << m->getType() << ")"
                  << " - Ano: " << m->getYear() 
                  << " - Média: " << m->getAverageScore() << "\n";
    }
}

void CLIView::showUserPage() {
    auto user = controller.getLoggedUser();
    if (!user) { 
        std::cout << "Nenhum usuário logado.\n"; 
        return; 
    }

    std::cout << "\n=== Página de " << user->getUsername() << " ===\n";
    std::cout << "Filmes assistidos: " << user->getWatchedCount() << "\n";
    std::cout << "Tempo total assistido (h): " << user->getTotalWatchTimeHours() << "\n";
    std::cout << "Última review: " << user->getLastReviewInfo() << "\n";
}

void CLIView::runAutoDemo() {
    controller.runAutoDemo();
}
