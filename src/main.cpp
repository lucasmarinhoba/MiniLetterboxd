#include <iostream>
#include "AppController.h"
#include "CLIView.h"

int main() {
    AppController controller;

    // Tenta carregar dados, se falhar, carrega defaults
    if(!controller.loadData()) {
        std::cout << "Inicializando dados padrão...\n";
        controller.loadDefaults();
    }

    CLIView view(controller);
    view.showMainMenu();

    // Ao sair, salva dados
    if(controller.saveData()) {
        std::cout << "Dados salvos com sucesso.\n";
    } else {
        std::cout << "Erro ao salvar dados.\n";
    }

    return 0;
}
