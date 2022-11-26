cmake_minimum_required(VERSION 3.16)
project(snakeCGP LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if (NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif ()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/opengl/snake")

find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets Widgets Multimedia MultimediaWidgets)

qt6_wrap_ui(menu/menuwidget.h menu/menuwidget.ui)

qt_add_executable(snake
        main.cpp
        geometries/vertexData.h
        game/gamewidget.cpp game/gamewidget.h
        geometries/snakegeometry.cpp geometries/snakegeometry.h
        geometries/planegeometry.cpp geometries/planegeometry.h
        menu/menuwidget.cpp menu/menuwidget.h menu/menuwidget.ui
        widgetstack.cpp widgetstack.h
        menu/options.cpp menu/options.h
        audio/soundengine.cpp audio/soundengine.h
        )

set_target_properties(snake PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        )

target_link_libraries(snake PUBLIC
        Qt::Core
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
        Qt::Multimedia
        Qt::MultimediaWidgets
        )

# Resources:
set(shaders_resource_files
        "shaders/fshader.glsl"
        "shaders/vshader.glsl"
        )

qt6_add_resources(snake "shaders"
        PREFIX
        "/"
        FILES
        ${shaders_resource_files}
        )

set(textures_resource_files
        "resources/cube.png"
        )

qt6_add_resources(snake "textures"
        PREFIX
        "/"
        FILES
        ${textures_resource_files}
        )

install(TARGETS snake
        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
        )
