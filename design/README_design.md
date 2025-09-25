# Mini Letterboxd – Design do Projeto (Etapa 1)

## 1️⃣ Visão Geral

Este documento descreve a **arquitetura e design** do projeto Mini Letterboxd, atendendo aos requisitos da **Etapa 1**:

- Headers (`.h`) das classes principais.
- Diagrama UML das classes.
- CMakeLists.txt inicial para build do projeto.

---

## 2️⃣ Estrutura de Diretórios

MiniLetterboxd/
│
├─ include/ # Arquivos headers (.h)
│ ├─ User.h
│ ├─ Media.h
│ ├─ Movie.h
│ ├─ Series.h
│ ├─ Review.h
│ ├─ FriendList.h
│ ├─ Persistence.h
│ ├─ AppController.h
│ ├─ CLIView.h
│ └─ GUIView.h
│
├─ design/ # UML e README do design
│ ├─ UML_MiniLetterboxd.png
│ └─ README_design.md
│
├─ src/ # Código fonte (main.cpp de teste opcional)
│
├─ CMakeLists.txt # Build inicial
│
└─ README.md # Descrição geral do projeto

---

## 3️⃣ Classes Principais

O projeto segue **Programação Orientada a Objetos**, com abstração, encapsulamento, herança e polimorfismo.  

### **Media (abstract)**
- Atributos: `title`, `synopsis`, `year`, `duration`, `cast`, `ratingAverage`.
- Métodos: `getTotalDuration()`, `getTitle()`, `setSynopsis()`, `addCastMember()`, `updateRating()`, `getRatingAverage()`.
- Subclasses: `Movie` e `Series`.

### **Movie**
- Representa um filme.
- Implementa `getTotalDuration()`.

### **Series**
- Representa uma série.
- Atributos: `seasons`, `episodesPerSeason`, `episodeDuration`.
- Métodos: `addSeason()`, `getTotalDuration()`.

### **Review**
- Avaliação de um usuário sobre uma mídia.
- Atributos: `media`, `score`, `text`, `date`.
- Métodos: `getMediaTitle()`, `getScore()`, `getText()`, `getDate()`.

### **User**
- Representa um usuário do sistema.
- Atributos: `username`, `password`, `reviews`, `friends`.
- Métodos: `addFriend()`, `addReview()`, `removeReview()`, `getReviews()`, `getWatchedCount()`, `getLastReviewInfo()`, `getTotalWatchTimeHours()`.

### **FriendList**
- Gerencia lista de amigos de um usuário.
- Métodos: `addFriend()`, `getFriends()`.

### **Persistence**
- Salva e carrega dados do sistema em arquivos.
- Métodos estáticos: `saveData()`, `loadData()`.

### **AppController**
- Controlador principal da aplicação.
- Atributos: `users`, `medias`, `loggedUser`.
- Métodos: `registerUser()`, `login()`, `addMovie()`, `addSeries()`, `addReview()`, `addFriend()`, `getLoggedUser()`.

### **CLIView**
- Interface em modo terminal.
- Métodos: `showMainMenu()`, `showUserPage()`, `listMedias()`.

### **GUIView (interface)**
- Interface abstrata para futuras GUIs.
- Métodos: `showLoginScreen()`, `showUserPage()`, `showFriends()`, `showMediaList()`, `showMediaDetails()`, `showReviews()`, `showAddReviewForm()`, `showMessage()`, `showError()`.

---

## 4️⃣ Diagrama UML

- Arquivo: `design/UML_MiniLetterboxd.png`  
- Representa: classes, atributos, métodos, heranças e relacionamentos.  
- Estilo: compacto, centralizado e visualmente equilibrado para leitura rápida.

---

## 5️⃣ CMakeLists.txt

- CMake inicial configurado para **C++17**.
- Inclui diretório `include/`.
- Compila todos os `.cpp` dentro de `src/`.
- Configura warnings para MSVC ou GCC/Clang.
- Permite instalação com `cmake --install .`.

**Exemplo de uso:**

```bash
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .

## 6️⃣ Justificativa do Design

O design do Mini Letterboxd foi elaborado considerando boas práticas de **Programação Orientada a Objetos (POO)** e escalabilidade do sistema.

### Principais pontos:

- **Separação de responsabilidades:**  
  Cada classe tem uma função bem definida, garantindo que alterações em uma funcionalidade não impactem outras partes do sistema.

- **Encapsulamento:**  
  Os atributos das classes são privados, com métodos públicos (getters/setters) controlando acesso e validação de dados.

- **Abstração e Polimorfismo:**  
  - `Media` é uma classe abstrata, permitindo que novas mídias sejam adicionadas sem alterar o código existente.  
  - `Movie` e `Series` implementam `getTotalDuration()`, exemplificando polimorfismo dinâmico.  
  - `GUIView` é uma interface abstrata, possibilitando múltiplas implementações (CLI, GUI).

- **Composição e associações:**  
  - `User` contém uma lista de `Review` e referências fracas para amigos (`weak_ptr`) evitando ciclos de memória.  
  - `AppController` gerencia usuários e mídias, garantindo centralização da lógica do sistema.

- **Facilidade de extensão:**  
  Novos tipos de mídia, interfaces ou funcionalidades podem ser implementados sem modificar as classes existentes.

- **Preparação para persistência:**  
  A classe `Persistence` foi isolada, permitindo salvar/carregar dados em arquivos e facilitando futuras integrações com banco de dados.

- **Consistência e manutenção:**  
  Cabeçalhos claros e documentação das classes facilitam compreensão do projeto e manutenção futura.


