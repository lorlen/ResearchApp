cmake_minimum_required(VERSION 3.14)
project(ResearchApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/src/designer")
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/include/*.h")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include(FetchContent)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)

FetchContent_Declare(
    picosha2
    GIT_REPOSITORY https://github.com/okdshin/PicoSHA2
)

FetchContent_MakeAvailable(json picosha2)

add_executable(ResearchApp)

target_compile_features(ResearchApp PUBLIC cxx_std_17)
target_compile_options(ResearchApp
    PRIVATE
        ${-Wall}
        ${-Wextra}
        ${-pedantic}
        $<$<CONFIG:Debug>:-Og>
)

target_sources(ResearchApp PRIVATE ${sources})

target_include_directories(ResearchApp
    PUBLIC
        $<BUILD_INTERFACE:${ResearchApp_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${picosha2_SOURCE_DIR}>
)

target_link_libraries(ResearchApp
    PRIVATE
        Qt5::Core
        Qt5::Widgets
        nlohmann_json::nlohmann_json
)
