cmake_minimum_required(VERSION 3.14)
project(ResearchApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/include/*.h")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(SQLite3)

include(FetchContent)

FetchContent_Declare(
    sqlite_orm
    GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
    GIT_TAG dev
)

FetchContent_Declare(
    picosha2
    GIT_REPOSITORY https://github.com/okdshin/PicoSHA2
)

FetchContent_MakeAvailable(sqlite_orm picosha2)

get_target_property(sqlite_orm_include sqlite_orm::sqlite_orm INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(sqlite_orm SYSTEM INTERFACE ${sqlite_orm_include})

add_executable(ResearchApp)

target_compile_features(ResearchApp PUBLIC cxx_std_17)
target_compile_options(ResearchApp
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
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
        sqlite_orm::sqlite_orm
)
