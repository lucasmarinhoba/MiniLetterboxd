#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <limits>

// Forward declaration para evitar dependência circular
class AppController;

class CLIView {
public:
    CLIView(AppController& ctrl);
    void showMainMenu();
    void listMedias();
    void showUserPage();
    void runAutoDemo();

private:
    AppController& controller;
};
