cmake_minimum_required(VERSION 3.14)
project(ResearchApp)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)

FetchContent_MakeAvailable(json)

add_subdirectory(src)