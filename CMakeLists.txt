cmake_minimum_required(VERSION 3.30)
project(sfml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ścieżka do folderu z plikami CMake SFML
set(SFML_DIR "C:/mingw/SFML-3.0.2/lib/cmake/SFML")

# Szukamy SFML w wersji 3 i wymaganych komponentach
find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics Audio)

# Tworzymy plik wykonywalny z main.cpp
add_executable(${PROJECT_NAME} main.cpp
        Paletka.h
        Pilka.h
        Stone.h)

# Linkujemy wszystkie potrzebne komponenty SFML
target_link_libraries(${PROJECT_NAME} PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
)

# (Opcjonalne) Kopiowanie DLL do katalogu z exe przy budowaniu
if (WIN32 AND SFML_DIR)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DIR}/../../../bin/sfml-system-3.dll"
            "${SFML_DIR}/../../../bin/sfml-window-3.dll"
            "${SFML_DIR}/../../../bin/sfml-graphics-3.dll"
            "${SFML_DIR}/../../../bin/sfml-audio-3.dll"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
