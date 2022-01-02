cmake_minimum_required(VERSION 3.19)
project(esi_atlir5_atlc_project2)

set(CMAKE_CXX_STANDARD 20)

set(QT_VERSION 6)
set(REQUIRED_LIBS Core Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Widgets Qt6::Network)

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

find_package(jsoncpp QUIET)
if (NOT jsoncpp_FOUND)
    message("jsoncpp not found, downloading from git.")
    Include(FetchContent)
    FetchContent_Declare(
            jsoncpp
            GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
            GIT_TAG 1.9.5)

    FetchContent_MakeAvailable(jsoncpp)

endif ()

include_directories(${jsoncpp_SOURCE_DIR}/include)
include(CTest)

#########################################################################################
# MODEL LIBRARY
#########################################################################################
set(MODEL_SOURCES
        src/model/game/matrix.cpp
        src/model/game/player.cpp
        src/model/tetrimino/tetrimino.cpp
        src/model/tetrimino/type/itetrimino.cpp
        src/model/tetrimino/type/jtetrimino.cpp
        src/model/tetrimino/type/ltetrimino.cpp
        src/model/tetrimino/type/otetrimino.cpp
        src/model/tetrimino/type/stetrimino.cpp
        src/model/tetrimino/type/ttetrimino.cpp
        src/model/tetrimino/type/ztetrimino.cpp
        src/model/game/tetriminoGenerator.cpp
        src/model/game/ongoinggame.cpp
        src/model/game/states/notstartedstate.cpp
        src/model/game/states/fallingstate.cpp
        src/model/game/states/lockeddownstate.cpp
        src/model/game/states/lockedoutstate.cpp
        src/model/game/states/stoppedstate.cpp
        src/model/game/states/blockedoutstate.cpp
        src/server/server/TetrisServer.cpp
        src/client/TetrisClient.cpp
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
        )

add_library(MODEL_LIB ${MODEL_SOURCES})

target_link_libraries(MODEL_LIB PUBLIC jsoncpp_lib ${REQUIRED_LIBS_QUALIFIED})

add_executable(model_test ${MODEL_TESTS})
target_link_libraries(model_test Catch2 MODEL_LIB)

#########################################################################################
# EXECUTABLES
#########################################################################################
add_executable(tetris_server src/server/main.cpp)
add_executable(tetris_client src/client/main.cpp)

target_link_libraries(tetris_client PUBLIC MODEL_LIB ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(tetris_server PUBLIC MODEL_LIB ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    set(DEBUG_SUFFIX)
    #if (CMAKE_BUILD_TYPE MATCHES "Debug")
    #    set(DEBUG_SUFFIX "d")
    #endif()
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
                "$<TARGET_FILE_DIR:tetris_client>/tetris_client/plugins/platforms/")
        add_custom_command(TARGET tetris_client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:tetris_client>/tetris_client/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Network)
        add_custom_command(TARGET tetris_client POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:tetris_client>")
    endforeach (QT_LIB)
endif ()

if (WIN32)
    set(DEBUG_SUFFIX)
    #if (CMAKE_BUILD_TYPE MATCHES "Debug")
    #    set(DEBUG_SUFFIX "d")
    #endif()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET tetris_server POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:tetris_server>/tetris_server/plugins/platforms/")
        add_custom_command(TARGET tetris_server POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:tetris_server>/tetris_server/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Network)
        add_custom_command(TARGET tetris_server POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:tetris_server>/tetris_server")
    endforeach (QT_LIB)
endif ()