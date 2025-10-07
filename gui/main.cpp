#include <QApplication>
#include "mainwindow.h"
#include "AppController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Inicializar controlador com dados defaults
    AppController controller;
    controller.loadDefaults();

    // Criar e mostrar a janela principal (tela inicial)
    MainWindow mainWindow(&controller);
    mainWindow.show();

    // Execução da aplicação Qt
    return a.exec();
}
