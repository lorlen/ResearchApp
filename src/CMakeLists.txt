include_directories(${ResearchApp_SOURCE_DIR}/include)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra")

find_package(Qt5Core)
find_package(Qt5Widgets)

add_executable(ResearchApp
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

        db/Database.cpp

        research/Date.cpp
        research/Research.cpp
        research/ResearchPoint.cpp
        research/Sensor.cpp
        research/User.cpp

        ../include/ui/NewSensorDialog.h
        ../include/ui/EditPointDialog.h
        ../include/ui/NewUserDialog.h ../include/db/Record.h)

target_link_libraries(ResearchApp Qt5::Core)
target_link_libraries(ResearchApp Qt5::Widgets)
