# Mini Letterboxd — Etapa 2 (CLI)

## 📦 Pré-requisitos
- **C++17** ou superior  
- **CMake** (>= 3.16)  
- Compilador (g++/clang++ no Linux/Mac ou MSVC no Windows)  

## ⚙️ Compilação

1. Clone este repositório:

   git clone https://github.com/SEU_USUARIO/MiniLetterboxd.git

   
   cd MiniLetterboxd
Crie a pasta de build e compile:

bash
Copiar código
mkdir build
cd build
cmake ..
cmake --build .
Isso irá gerar o executável MiniLetterboxd dentro da pasta build/.

▶️ Execução
No Linux/Mac:

bash
Copiar código
./MiniLetterboxd
No Windows (PowerShell):

powershell
Copiar código
.\MiniLetterboxd.exe
🧪 Funcionalidades disponíveis no CLI
No menu principal, você poderá:

Registrar usuário

Fazer login

Adicionar filme/série

Listar filmes/séries

Avaliar (nota + review)

Listar amigos e reviews de amigos

Salvar e carregar dados (persistência em arquivos .txt)

⚠️ Os dados de usuários, filmes e reviews são salvos automaticamente em arquivos de texto na pasta data/.
Ao rodar novamente, o programa carregará esses dados.