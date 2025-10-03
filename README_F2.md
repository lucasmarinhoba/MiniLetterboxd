# Mini Letterboxd — Etapa 2 (CLI)

## 📦 Pré-requisitos
- **C++17** ou superior  
- **CMake** (>= 3.16)  
- Compilador:
  - **Windows**: [MinGW](http://mingw-w64.org/) (instalado e configurado no PATH)  
  - **Linux/Mac**: g++ ou clang  

---

## ⚙️ Compilação

### 🔹 Windows (MinGW)
Abra o **PowerShell** ou **Prompt de Comando** na pasta do projeto e execute:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
Isso criará a pasta build/ e gerará o executável MiniLetterboxd.exe dentro dela.

🔹 Linux/Mac
Abra o terminal na pasta do projeto e execute:

bash
Copiar código
cmake -S . -B build
cmake --build build
Isso criará a pasta build/ e gerará o executável MiniLetterboxd.

▶️ Execução
🔹 Windows (PowerShell)
powershell
Copiar código
cd build
.\MiniLetterboxd.exe
🔹 Linux/Mac
bash
Copiar código
cd build
./MiniLetterboxd
🧪 Funcionalidades disponíveis no CLI
No menu principal, você poderá:

Registrar usuário

Fazer login

Adicionar filme/série

Listar filmes/séries

Avaliar (nota + review)

Listar amigos e reviews de amigos (em construção)

Salvar e carregar dados (persistência em arquivos .txt)

⚠️ Os dados de usuários, filmes e reviews são salvos automaticamente em arquivos de texto na pasta data/.
Ao rodar novamente, o programa carregará esses dados