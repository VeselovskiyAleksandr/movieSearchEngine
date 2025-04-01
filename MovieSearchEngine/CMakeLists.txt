# CMakeList.txt: проект CMake для MovieSearchEngine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (MovieSearchEngine  "include/MovieSearchEngine.h" "include/Configuration.h" "include/ConverterJSON.h" "include/Entry.h"   "src/ConverterJSON.cpp" "src/MovieSearchEngine.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_link_libraries(MovieSearchEngine PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(MovieSearchEngine PUBLIC include)