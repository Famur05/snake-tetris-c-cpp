cmake_minimum_required(VERSION 3.16)

project(s21_Snake VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        gui/desktop/main.cc
        gui/desktop/mainwindow.cc
        gui/desktop/mainwindow.h
        gui/desktop/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(s21_Snake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gui/desktop/mywidgetsnake.h gui/desktop/mywidgetsnake.cc
        gui/desktop/snakewindow.h gui/desktop/snakewindow.cc gui/desktop/snakewindow.ui
        brick_game/snake/controller.h brick_game/snake/controller.cc
        brick_game/snake/model.h brick_game/snake/model.cc
        gui/desktop/tetriswindow.h gui/desktop/tetriswindow.cc gui/desktop/tetriswindow.ui
        gui/desktop/mywidgettetris.h gui/desktop/mywidgettetris.cc
        brick_game/tetris/backend.h brick_game/tetris/backend.c
        brick_game/tetris/fsm.h brick_game/tetris/fsm.c
        brick_game/tetris/tetris_lib.h brick_game/tetris/tetris_lib.c
        gui/desktop/nextfigure.h gui/desktop/nextfigure.cc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET s21_Snake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(s21_Snake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(s21_Snake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(s21_Snake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.s21_Snake)
endif()
set_target_properties(s21_Snake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS s21_Snake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(s21_Snake)
endif()
