#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <limits>

// Forward declaration para evitar dependência circular
class AppController;
class User;

class CLIView {
public:
    // Construtor
    CLIView(AppController& ctrl);

    // Menu inicial (Registrar/Login/Sair)
    void showMainMenu();

    // Menu do usuário logado (após login)
    void showUserMenu();

    // Listar todas as mídias com média de reviews
    void listMedias();

    // Mostrar página do usuário logado
    void showUserPage();

    // Executar auto-demo
    void runAutoDemo();

    // Listar amigos do usuário logado
    void listFriends(std::shared_ptr<User> user);

private:
    AppController& controller;  // referência ao controller principal

    // Pausa a tela até que o usuário pressione Enter
    void pause();
};
