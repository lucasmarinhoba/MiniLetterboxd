#pragma once
#include "AppController.h"

class CLIView {
private:
    AppController& controller;

public:
    CLIView(AppController& controller);

    void showMainMenu();
    void showUserPage();
    void listMedias();
};
