include_directories(${projekt_SOURCE_DIR}/include)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra -D_Debug")

find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(projekt
        main.cpp
        globals.cpp
        ui/LoginWindow.cpp
        ui/MainWindow.cpp
        ui/NewSensorDialog.cpp
        ui/EditPointDialog.cpp
        ui/EditResearchersDialog.cpp
        ui/SensorListDialog.cpp
        ui/ListItemWithID.cpp
        ui/NewUserDialog.cpp
        db/database.cpp
        db/user.cpp
        db/sha256.cpp
        db/cipher.cpp
        db/exceptions.cpp
        research/date.cpp
        research/research.cpp
        research/researchpoint.cpp
        research/sensor.cpp
        ../include/ui/NewSensorDialog.h
        ../include/ui/EditPointDialog.h
        ../include/ui/NewUserDialog.h)

target_link_libraries(projekt Qt5::Core)
target_link_libraries(projekt Qt5::Widgets)
