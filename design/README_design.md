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
├─ src/ 
│
├─ CMakeLists.txt 
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

1. Separação de Responsabilidades

O projeto foi dividido em classes com papéis bem definidos, seguindo o princípio da responsabilidade única:

AppController: centraliza a lógica de negócio. É responsável por operações como cadastro e login de usuários, criação de mídias e adição de reviews. Não trata interface nem persistência, evitando mistura de camadas.

CLIView: responsável apenas pela interação em linha de comando, exibindo menus e chamando os métodos do controlador.

Persistence: lida unicamente com o salvamento e carregamento de dados. Se futuramente for necessário trocar de .txt para JSON ou banco de dados, somente essa classe será alterada.

Essa organização facilita a manutenção e a evolução do sistema, permitindo alterar ou substituir módulos de forma independente.

2. Encapsulamento

Todos os atributos são privados, e o acesso ocorre apenas por métodos públicos controlados. Isso garante consistência e proteção dos dados:

Em User, o atributo password nunca é exposto diretamente. O acesso é feito via método checkPassword(), evitando manipulação indevida da senha.

Em Media, a média de avaliação (ratingAverage) só pode ser alterada pelo método updateRating(), que permite aplicar regras de validação antes de atualizar o valor.

A lista de amigos em User é armazenada via weak_ptr, protegendo contra ciclos de memória e mantendo o controle do sistema sobre como essa informação é acessada.

Esse modelo garante maior segurança e consistência, reduzindo erros de acesso direto a atributos.

3. Abstração e Polimorfismo

A classe Media é abstrata, definindo o método puro getTotalDuration(). Isso permite que Movie e Series implementem suas próprias versões, sem impactar o restante do sistema.

A interface GUIView estabelece os métodos necessários para qualquer implementação de interface (linha de comando, GUI em Qt etc.). Assim, diferentes modos de interação podem ser adicionados sem alterar a lógica principal.

Esse uso de abstração e polimorfismo garante extensibilidade e flexibilidade.

4. Composição e Associações

User contém uma lista de Review e referências fracas para amigos, representando relações reais entre usuários.

AppController compõe listas de usuários e mídias, funcionando como ponto central de orquestração.

O relacionamento entre Media e Review mostra a associação natural: cada mídia pode ter várias avaliações, e cada avaliação pertence a um usuário.

Esses vínculos representam corretamente o domínio do problema e foram projetados para evitar dependências desnecessárias.

5. Extensibilidade

O design facilita a adição de novas funcionalidades:

Novos tipos de mídia (como Documentary ou MiniSeries) podem ser implementados estendendo Media.

Outras interfaces gráficas podem ser adicionadas implementando GUIView.

A camada de persistência pode ser expandida para suportar diferentes formatos de dados.

Assim, o sistema está preparado para crescer sem que classes já existentes precisem ser modificadas.

6. Preparação para Persistência

A classe Persistence foi isolada, lidando exclusivamente com leitura/escrita de dados. Isso facilita futuras integrações com arquivos em outros formatos ou bancos de dados relacionais, sem impacto na lógica do sistema.

7. Consistência e Manutenção

Arquivos .h concentram apenas interfaces e definições de classes.

Métodos seguem uma nomenclatura clara (getUsername, addReview, getTotalDuration).

O uso de smart pointers (shared_ptr, weak_ptr) garante gerenciamento automático de memória, reduzindo riscos de vazamentos.

Essa padronização contribui para clareza, legibilidade e facilidade de manutenção.
