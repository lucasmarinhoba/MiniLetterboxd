cmake_minimum_required(VERSION 3.16)

project(MiniLetterboxd VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ===================== Fontes =====================
set(SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/AppController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CLIView.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/User.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Review.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Persistence.cpp"
)

# ===================== Executável =====================
add_executable(${PROJECT_NAME} ${SOURCES})

# ===================== Flags do compilador =====================
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

# ===================== Instalação =====================
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# ===================== Debug =====================
message(STATUS "Arquivos fonte detectados:")
foreach(SRC ${SOURCES})
    message(STATUS "  - ${SRC}")
endforeach()
