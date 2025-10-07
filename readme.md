# Mini Letterboxd

## Descrição do Projeto
Mini Letterboxd é uma aplicação em C++ que simula funcionalidades de uma rede social de filmes e séries, permitindo que usuários registrem mídias assistidas, adicionem reviews, avaliem produções, gerenciem amigos e visualizem atividades.  

Este projeto é uma **adaptação da sugestão de tema "Agenda"**, proposta originalmente para exercícios de Programação Orientada a Objetos (POO). A adaptação manteve o foco em conceitos de POO e design de software, substituindo compromissos e tarefas por filmes, séries e reviews, enquanto preserva a lógica de usuários, relacionamentos e registros.

O projeto foi implementado usando:
- C++ moderno (C++17)
- Qt para interface gráfica (GUI)
- STL (`vector`, `string`, `shared_ptr`, `weak_ptr`) para gerenciamento de coleções
- RAII e smart pointers para gerenciamento de memória
- Persistência em arquivos `.txt` para salvar dados entre execuções

---
📦MiniLetterboxd
 ┣ 📂data
 ┃ ┣ 📜friends.txt
 ┃ ┣ 📜medias.txt
 ┃ ┣ 📜reviews.txt
 ┃ ┗ 📜users.txt
 ┣ 📂design
 ┃ ┣ 📜README_design.md
 ┃ ┗ 📜UML_MiniLetterboxd.png
 ┣ 📂gui
 ┃ ┣ 📜addfrienddialog.cpp
 ┃ ┣ 📜addfrienddialog.h
 ┃ ┣ 📜addfrienddialog.ui
 ┃ ┣ 📜addmoviedialog.cpp
 ┃ ┣ 📜addmoviedialog.h
 ┃ ┣ 📜addmoviedialog.ui
 ┃ ┣ 📜addreviewdialog.cpp
 ┃ ┣ 📜addreviewdialog.h
 ┃ ┣ 📜addreviewdialog.ui
 ┃ ┣ 📜addseriesdialog.cpp
 ┃ ┣ 📜addseriesdialog.h
 ┃ ┣ 📜addseriesdialog.ui
 ┃ ┣ 📜CMakeLists.txt
 ┃ ┣ 📜CMakeLists.txt.user
 ┃ ┣ 📜deletefrienddialog.cpp
 ┃ ┣ 📜deletefrienddialog.h
 ┃ ┣ 📜deletefrienddialog.ui
 ┃ ┣ 📜deletereviewdialog.cpp
 ┃ ┣ 📜deletereviewdialog.h
 ┃ ┣ 📜deletereviewdialog.ui
 ┃ ┣ 📜friendactivitydialog.cpp
 ┃ ┣ 📜friendactivitydialog.h
 ┃ ┣ 📜friendactivitydialog.ui
 ┃ ┣ 📜listmediasdialog.cpp
 ┃ ┣ 📜listmediasdialog.h
 ┃ ┣ 📜listmediasdialog.ui
 ┃ ┣ 📜main.cpp
 ┃ ┣ 📜mainwindow.cpp
 ┃ ┣ 📜mainwindow.h
 ┃ ┣ 📜mainwindow.ui
 ┃ ┣ 📜registerdialog.cpp
 ┃ ┣ 📜registerdialog.h
 ┃ ┣ 📜registerdialog.ui
 ┃ ┣ 📜usermenuwindow.cpp
 ┃ ┣ 📜usermenuwindow.h
 ┃ ┣ 📜usermenuwindow.ui
 ┃ ┣ 📜userpagedialog.cpp
 ┃ ┣ 📜userpagedialog.h
 ┃ ┗ 📜userpagedialog.ui
 ┣ 📂include
 ┃ ┣ 📜AppController.h
 ┃ ┣ 📜CLIView.h
 ┃ ┣ 📜FriendList.h
 ┃ ┣ 📜GUIView.h
 ┃ ┣ 📜Media.h
 ┃ ┣ 📜Movie.h
 ┃ ┣ 📜Persistence.h
 ┃ ┣ 📜Review.h
 ┃ ┣ 📜Series.h
 ┃ ┗ 📜User.h
 ┣ 📂src
 ┃ ┣ 📜AppController.cpp
 ┃ ┣ 📜CLIView.cpp
 ┃ ┣ 📜FriendList.cpp
 ┃ ┣ 📜Media.cpp
 ┃ ┣ 📜Persistence.cpp
 ┃ ┣ 📜Review.cpp
 ┃ ┣ 📜Series.cpp
 ┃ ┗ 📜User.cpp
 ┣ 📜CMakeLists.txt
 ┗ 📜readme.md

## Funcionalidades

- **Registro e login de usuários**
- **Adição e gerenciamento de amigos**
- **Adição de filmes e séries** (com temporadas e episódios)
- **Adição, remoção e visualização de reviews**
- **Página do usuário** mostrando histórico de avaliações e estatísticas
- **Visualização da atividade dos amigos**
- **Persistência de dados** entre execuções
- **Auto-demo** para teste rápido das funcionalidades

# Mapeamento de Conceitos de POO no Mini Letterboxd

## 1. Abstração & Encapsulamento
- **Como foi usado:** Separação clara de interface (`.h`) e implementação (`.cpp`). Campos privados com getters e setters, garantindo encapsulamento e validação.
- **Exemplos:**
  - `User.h/cpp`: campos `username`, `password` privados, métodos `getUsername()`, `checkPassword()`.
  - `Media.h/cpp`: métodos virtuais puros `getTotalDuration()`, `getType()`, `isSeries()` e campos privados.
  - `GUIView.h`: interface abstrata para todas as implementações da GUI.

## 2. Classes e Objetos
- **Como foi usado:** Projeto estruturado em classes coerentes para domínio (modelos), controle (AppController) e apresentação (CLIView / GUIView / Qt).
- **Exemplos:**
  - `AppController.h/cpp`: gerencia listas de usuários e mídias, orquestra chamadas entre view e modelo.
  - `CLIView.cpp` e `MainWindow.cpp`/`UserMenuWindow.cpp`: instâncias de interface interagem com o controller.

## 3. Herança & Polimorfismo
- **Como foi usado:** Hierarquia de classes `Media` → `Movie` / `Series`, com métodos virtuais que permitem polimorfismo dinâmico.
- **Exemplos:**
  - `Media.h/cpp`: classe abstrata com métodos virtuais puros.
  - `Movie.h/cpp` e `Series.h/cpp`: herdam de `Media` e implementam os métodos.
  - `GUIView.h`: interface para múltiplas implementações de GUI (Qt, CLI).

## 4. Composição vs Herança
- **Como foi usado:**
  - **Composição:** `User` contém listas de reviews, friends e watchedMedias; `AppController` contém `Persistence` e listas de objetos.
  - **Herança:** Usada apenas onde há especialização natural (`Media` → `Movie` / `Series`).
- **Exemplos:**
  - `User.h/cpp` (composição de `Review`, `Media` e `User` via smart pointers).
  - `AppController.h/cpp` (composição de `Persistence`).

## 5. Polimorfismo dinâmico
- **Como foi usado:** Manipulação de `Media` de forma polimórfica via `shared_ptr<Media>` sem necessidade de `dynamic_cast`.
- **Exemplos:**
  - `vector<shared_ptr<Media>>` no `AppController` para filmes e séries.
  - Chamadas a `getTotalDuration()`, `getType()` ou `isSeries()` são resolvidas em tempo de execução.

## 6. Gerenciamento de recursos
- **Como foi usado:** 
  - Smart pointers (`shared_ptr`, `weak_ptr`) para gerenciar memória.
  - RAII aplicado em arquivos na classe `Persistence`.
- **Exemplos:**
  - `User.h/cpp`, `Media.h/cpp`, `Review.h/cpp` para objetos complexos.
  - `Persistence.h/cpp` para leitura e escrita de dados.

## 7. Templates e STL
- **Como foi usado:** Containers STL para gerenciar coleções de objetos, funções genéricas para manipulação de listas.
- **Exemplos:**
  - `vector`, `string`, `weak_ptr`, `shared_ptr`, `function`.
  - Listas de amigos (`vector<weak_ptr<User>>`), reviews (`vector<shared_ptr<Review>>`) e mídias (`vector<shared_ptr<Media>>`).

## 8. Sobrecarga de operadores
- **Como foi usado:** Embora o projeto não exija sobrecarga crítica, poderia ser implementada em `Review` para ordenar por data ou nota.
- **Sugestão:** `Review.h/cpp` implementar `operator<` para ordenação.

## 9. Tratamento de exceções
- **Como foi usado:** Métodos retornam `bool` e mensagens (`string&`) para sinalizar erros, e validações internas para evitar estados inválidos.
- **Exemplos:**
  - `AppController.h/cpp` valida login, registro e operações de amizade.
  - `Persistence.h/cpp` trata falhas de arquivo e formato inválido.

## 10. Documentação técnica e UML
- **Como foi usado:** Diagramas UML foram gerados para núcleo e GUI, e o README detalha arquitetura, fluxos Controller ↔ View ↔ Model.
- **Exemplos:**
  - Diagramas de classes `.puml`.
  - README.md descrevendo design e instruções de build.

## 11. Build automatizado
- **Como foi usado:** Projeto configurado com CMake para núcleo e GUI. Qt configurado com `AUTOUIC`, `AUTOMOC` e `AUTORCC`.
- **Exemplos:**
  - `CMakeLists.txt` com instruções de build para Linux/Windows.
  - Integração de fontes do núcleo (`.cpp`) e da GUI (Qt `.ui` e `.cpp`).

## Instruções de Compilação

### Pré-requisitos
- **CMake** (>= 3.16)
- **Qt 6** (ou Qt 5 compatível)
- Compilador C++17 (MSVC, GCC ou Clang)

---

### Windows

bash
cd caminho\para\MiniLetterboxd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build
\MiniLetterboxd.exe
### Linux
bash
cd /caminho/para/MiniLetterboxd
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/caminho/para/Qt/lib/cmake
make
./MiniLetterboxd
### macOS
bash
cd /caminho/para/MiniLetterboxd
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/caminho/para/Qt/lib/cmake
make
./MiniLetterbox


[Assista ao vídeo](https://drive.google.com/file/d/1zakhHm7d_ll2c5rPUapV5bT1d0nJkMAx/view?usp=sharing)