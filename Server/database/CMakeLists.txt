cmake_minimum_required(VERSION 3.13)
project(gimpdocs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)
find_package(Qt5Sql REQUIRED)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(gimpdocs main.cpp collegamentoDB.h collegamentoDB.cpp sha256.h sha256.cpp ./../server.cpp ./../server.h)
target_link_libraries(gimpdocs ${LIBRARIES})
target_link_libraries(gimpdocs Qt5::Core Qt5::Quick Qt5::Sql)