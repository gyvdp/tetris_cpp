cmake_minimum_required(VERSION 3.19)
project(esi_atlir5_atlc_project2)

set(CMAKE_CXX_STANDARD 20)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets Qt6::Network)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall")

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_PREFIX_PATH $ENV{QTDIR})
endif ()

include_directories(include)
include_directories(resources)
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
        src/model/tetrimino/tetrimino.cpp
        src/model/game/tetriminoGenerator.cpp
        src/model/game/ongoinggame.cpp
        src/model/game/states/notstartedstate.cpp
        src/model/game/states/fallingstate.cpp
        src/model/game/states/lockeddownstate.cpp
        src/model/game/states/lockedoutstate.cpp
        src/model/game/states/stoppedstate.cpp
        src/model/game/states/blockedoutstate.cpp
        src/model/notification/notification.cpp
        )

set(MODEL_TESTS
        test/main_test.cpp
        test/model/game/player_test.cpp
        test/model/tetrimino/orientation_test.cpp
        ###############REPLACE AT GOOD PLACE
        test/utils/coordinate_test.cpp
        test/model/tetrimino/tetrimino_test.cpp
        test/model/tetrimino/type/itetrimino_test.cpp
        test/model/tetrimino/type/jtetrimino_test.cpp
        test/model/tetrimino/type/ltetrimino_test.cpp
        test/model/tetrimino/type/otetrimino_test.cpp
        test/model/tetrimino/type/stetrimino_test.cpp
        test/model/tetrimino/type/ttetrimino_test.cpp
        test/model/tetrimino/type/ztetrimino_test.cpp
        test/model/game/matrix_test.cpp
        test/model/tetrimino/direction_test.cpp
        test/model/game/tetriminoGenerator_test.cpp
        test/model/game/state/fallingstate_test.cpp
        test/model/game/state/blockedoutstate_test.cpp
        test/model/game/state/lockedoutstate_test.cpp
        test/model/game/state/lockeddownstate_test.cpp
        test/model/game/state/notstartedstate_test.cpp
        test/model/game/state/stoppedstate_test.cpp
        )

add_library(MODEL_LIB ${MODEL_SOURCES})
target_link_libraries(MODEL_LIB Boost::system Boost::thread)

target_link_libraries(MODEL_LIB PUBLIC ${REQUIRED_LIBS_QUALIFIED})

add_executable(model_test ${MODEL_TESTS})
target_link_libraries(model_test Catch2 MODEL_LIB)

#########################################################################################
# SERVER LIBRARY
#########################################################################################
set(SERVER_SOURCES
        src/server/tetris_server.cpp
        src/server/match.cpp
        src/server/player_socket.hpp
        )

set(SERVER_TESTS
        test/main_test.cpp
        )

add_library(SERVER_LIB ${SERVER_SOURCES} ${MODEL_SOURCES})

target_link_libraries(SERVER_LIB PUBLIC ${REQUIRED_LIBS_QUALIFIED})

add_executable(server_test ${SERVER_TESTS})
target_link_libraries(server_test Catch2 SERVER_LIB)

#########################################################################################
# VIEW
#########################################################################################
set(VIEW_SOURCES
        resources/resources.qrc
        src/client/view/component/mino.cpp
        src/client/view/component/matrix.cpp
        src/client/view/scene/game_scene.cpp
        src/client/view/window/game_window.cpp
        src/client/view/view.cpp
        )

add_library(VIEW_LIB ${VIEW_SOURCES})
target_link_libraries(VIEW_LIB PUBLIC ${REQUIRED_LIBS_QUALIFIED})

#########################################################################################
# CLIENT LIBRARY
#########################################################################################
set(CLIENT_SOURCES
        src/client/tetris_client.cpp
        )

set(CLIENT_TESTS
        test/main_test.cpp
        )

add_library(CLIENT_LIB ${CLIENT_SOURCES})

target_link_libraries(CLIENT_LIB PUBLIC MODEL_LIB VIEW_LIB ${REQUIRED_LIBS_QUALIFIED})

add_executable(client_test ${CLIENT_TESTS})
target_link_libraries(client_test Catch2 CLIENT_LIB)

#########################################################################################
# EXECUTABLES
#########################################################################################
add_executable(tetris_server src/server/main.cpp)
add_executable(tetris_client src/client/main.cpp resources/resources.qrc)

target_link_libraries(tetris_client PUBLIC MODEL_LIB SERVER_LIB CLIENT_LIB ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(tetris_server PUBLIC MODEL_LIB SERVER_LIB CLIENT_LIB ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET tetris_client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:tetris_client>/plugins/platforms/")
        add_custom_command(TARGET tetris_client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:tetris_client>/plugins/platforms/")
        if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
            add_custom_command(TARGET tetris_server POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory
                    "$<TARGET_FILE_DIR:tetris_server>/plugins/platforms/")
            add_custom_command(TARGET tetris_server POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:tetris_server>/plugins/platforms/")
        endif ()
        foreach (QT_LIB Core Gui Widgets Network)
            add_custom_command(TARGET tetris_client POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:tetris_client>")
        endforeach (QT_LIB)
        foreach (QT_LIB Core Gui Widgets Network)
            add_custom_command(TARGET tetris_server POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                    "$<TARGET_FILE_DIR:tetris_server>")
        endforeach (QT_LIB)
    endif ()
endif ()