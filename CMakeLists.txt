cmake_minimum_required(VERSION 3.19)
project(esi_atlir5_atlc_project2)

set(CMAKE_CXX_STANDARD 20)

set(QT_VERSION 6)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wno-unused-variable")

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_PREFIX_PATH $ENV{QTDIR})
endif ()

include_directories(src resources)

#########################################################################################
# SET UP / DOWNLOAD NEEDED LIBRARIES
#########################################################################################
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets Qt6::Network)
set(CMAKE_AUTOMOC ON)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

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
        test/model/tetrimino/tetriminologic_test.cpp
        )

add_library(MODEL_LIB ${MODEL_SOURCES})

target_link_libraries(MODEL_LIB PUBLIC ${REQUIRED_LIBS_QUALIFIED})

add_executable(model_test ${MODEL_TESTS})
target_link_libraries(model_test Catch2 MODEL_LIB)

#########################################################################################
# TETRIS SERVER LIBRARY
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
set_property(TARGET SERVER_LIB PROPERTY AUTOMOC ON)
add_executable(server_test ${SERVER_TESTS})
target_link_libraries(server_test Catch2 SERVER_LIB)

#########################################################################################
# TETRIS CLIENT LIB
#########################################################################################
set(CLIENT_SOURCES
        resources/resources.qrc
        src/client/client.cpp
        src/client/window/game_window.cpp
        src/client/scene/multiplayer_scene.cpp
        src/client/component/mino.cpp
        src/client/component/matrix.cpp
        src/client/component/game.cpp
        src/client/socket_client.cpp
        src/client/component/score_board.cpp
        src/client/component/tetri_holder.cpp
        )


add_library(CLIENT_LIB ${CLIENT_SOURCES})
target_link_libraries(CLIENT_LIB PUBLIC MODEL_LIB ${REQUIRED_LIBS_QUALIFIED})
set_property(TARGET CLIENT_LIB PROPERTY AUTORCC ON)

#########################################################################################
# EXECUTABLES
#########################################################################################
add_executable(tetris_server src/server/main.cpp)
add_executable(tetris_client src/client/main.cpp)

target_link_libraries(tetris_client PUBLIC CLIENT_LIB ${REQUIRED_LIBS_QUALIFIED})
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