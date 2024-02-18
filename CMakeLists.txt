cmake_minimum_required(VERSION 3.22)
project(GtkSandbox VERSION 1.1.5)
set(PROJECT_TARGET sandbox)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ./src)
set(PROJECT_BINARY_DIR ./target)
set(PROJECT_RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(MY_SOURCES
        src/main.c
        src/version.h
        src/utils/os_interface.c
        src/utils/os_interface.h
        src/models/app_model.h
        src/views/common/view_builder.c
        src/views/common/view_builder.h
        src/views/common/view_styler.c
        src/views/common/view_styler.h
        src/views/app_wnd/app_view.c
        src/views/app_wnd/app_view.h
        src/models/app_model.c
        src/controllers/app_ctrl.c
        src/controllers/app_ctrl.h
        src/utils/parse_args.c
        src/utils/parse_args.h src/common_defs.h)
set(IMAGES_DIR ${PROJECT_RESOURCE_DIR}/images)
set(STYLE_DIR ${PROJECT_RESOURCE_DIR}/style)
set(SCSS_SOURCE ${STYLE_DIR}/sandbox_style.scss)
set(CSS_OUTFILE ${PROJECT_BINARY_DIR}/sandbox_style.css)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--export-dynamic")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
add_link_options(-rdynamic)
add_compile_options(-pedantic -Wall -Wextra)

include_directories(${PROJECT_SOURCE_DIR})

configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_SOURCE_DIR}/version.h")

# GTK stuff
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(${PROJECT_TARGET} ${MY_SOURCES})

target_include_directories(${PROJECT_TARGET} PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(${PROJECT_TARGET} ${GTK3_LIBRARIES})

add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD COMMAND sassc -t expanded ${SCSS_SOURCE} ${CSS_OUTFILE})
configure_file(${PROJECT_SOURCE_DIR}/sandbox.glade ${PROJECT_BINARY_DIR}/sandbox.glade COPYONLY)