cmake_minimum_required(VERSION 3.16)

# Nome e versão do projeto
project(MiniLetterboxd VERSION 1.0 LANGUAGES CXX)

# ===================== Configurações de C++ =====================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===================== Diretórios =====================
# Inclui headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Fonte do projeto: todos os .cpp dentro de src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ===================== Executável =====================
add_executable(${PROJECT_NAME} ${SOURCES})

# ===================== Flags do compilador =====================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

# ===================== Diretório de instalação =====================
# Permite "make install" ou "cmake --install ."
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# ===================== Dependências futuras =====================
# Exemplo de Qt
# find_package(Qt5 REQUIRED COMPONENTS Widgets)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

# Outras bibliotecas externas
# add_subdirectory(external/libname)
# target_link_libraries(${PROJECT_NAME} PRIVATE libname)
