cmake_minimum_required(VERSION 3.19)
project(esi_atlir5_atlc_project2)

set(CMAKE_CXX_STANDARD 20)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall")
endif ()

include_directories(include)
include_directories(src)

#########################################################################################
# SET UP / DOWNLOAD NEEDED LIBRARIES
#########################################################################################
find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
    message("Catch not found, downloading from git.")
    Include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.6)
    FetchContent_MakeAvailable(Catch2)
endif ()

include(CTest)

#########################################################################################
# MODEL LIBRARY
#########################################################################################
set(MODEL_SOURCES
        src/model/game/matrix.cpp
        src/model/tetrimino/tetrimino.cpp)

add_library(MODEL_LIB ${MODEL_SOURCES})


#########################################################################################
# EXECUTABLES
#########################################################################################
add_executable(tetris_server src/server/main.cpp)
add_executable(tetris_client src/client/main.cpp)

target_link_libraries(tetris_client ${REQUIRED_LIBS_QUALIFIED} ${MODEL_LIB})
target_link_libraries(tetris_server ${REQUIRED_LIBS_QUALIFIED} ${MODEL_LIB})

