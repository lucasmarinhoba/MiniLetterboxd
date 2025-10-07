cmake_minimum_required(VERSION 3.16)

project(MiniLetterboxd VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Include ----
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ======== Qt ========
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ======== Fontes ========
set(SOURCES
    src/AppController.cpp
    src/CLIView.cpp
    src/User.cpp
    src/Review.cpp
    src/Persistence.cpp
    src/FriendList.cpp
    src/Series.cpp
    src/Media.cpp

    # GUI
    gui/main.cpp
    gui/mainwindow.cpp
    gui/registerdialog.cpp
    gui/usermenuwindow.cpp
    gui/userpagedialog.cpp
    gui/addmoviedialog.cpp
    gui/addseriesdialog.cpp
    gui/addreviewdialog.cpp
    gui/deletereviewdialog.cpp
    gui/addfrienddialog.cpp
    gui/deletefrienddialog.cpp
    gui/listmediasdialog.cpp
)

set(HEADERS
    include/AppController.h
    include/CLIView.h
    include/FriendList.h
    include/GUIView.h
    include/Media.h
    include/Movie.h
    include/Persistence.h
    include/Review.h
    include/Series.h
    include/User.h

    gui/mainwindow.h
    gui/registerdialog.h
    gui/usermenuwindow.h
    gui/userpagedialog.h
    gui/addmoviedialog.h
    gui/addseriesdialog.h
    gui/addreviewdialog.h
    gui/deletereviewdialog.h
    gui/addfrienddialog.h
    gui/deletefrienddialog.h
    gui/listmediasdialog.h
)

set(UI_FILES
    gui/mainwindow.ui
    gui/registerdialog.ui
    gui/usermenuwindow.ui
    gui/userpagedialog.ui
    gui/addmoviedialog.ui
    gui/addseriesdialog.ui
    gui/addreviewdialog.ui
    gui/deletereviewdialog.ui
    gui/addfrienddialog.ui
    gui/deletefrienddialog.ui
    gui/listmediasdialog.ui
)

# ======== Executável ========
qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    gui/friendactivitydialog.h gui/friendactivitydialog.cpp gui/friendactivitydialog.ui
)

# ======== Libraries ========
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

# ======== Compile options ========
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

# ======== Criação da pasta data ========
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

# ======== Define PROJECT_SOURCE_DIR no código ========
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

# ======== Install ========
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# ======== Debug: lista arquivos ========
message(STATUS "Arquivos fonte detectados:")
foreach(SRC ${SOURCES})
    message(STATUS "  - ${SRC}")
endforeach()
