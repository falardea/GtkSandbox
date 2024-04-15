cmake_minimum_required(VERSION      3.16)

project(GtkSandbox VERSION          1.2.2)

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(PROJECT_TARGET sandbox)
set(CSS_TARGET sandbox_style.css)

set(CMAKE_C_STANDARD                11)
set(CMAKE_CXX_STANDARD              11)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
add_compile_options(${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS} -Wall -Wextra -rdynamic)
add_link_options(-rdynamic)

set(PROJECT_SOURCE_DIR              ./src)
set(PROJECT_BINARY_DIR              ./target)
set(PROJECT_RESOURCE_DIR            ${CMAKE_SOURCE_DIR}/resources)

set(GRESOURCE_C                     sandbox.gresource.c)
set(GRESOURCE_XML                   sandbox.gresource.xml)

set(IMAGES_DIR                      ${PROJECT_RESOURCE_DIR}/images)
set(SPINNER_FILE                    ${IMAGES_DIR}/my_spinner200x200_50fps.gif)
set(STYLE_DIR                       ${PROJECT_RESOURCE_DIR}/style)
set(SCSS_SOURCE                     ${STYLE_DIR}/scss/sandbox_style.scss)
set(CSS_OUTFILE                     ${STYLE_DIR}/${CSS_TARGET})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# This will build our resource bundle
# From: https://stackoverflow.com/questions/63697778/how-to-use-glib-compile-resources-with-cmake
add_custom_command(
      OUTPUT ${GRESOURCE_C}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${GLIB_COMPILE_RESOURCES}
      ARGS
      --generate-source
      --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
      ${PROJECT_RESOURCE_DIR}/${GRESOURCE_XML}
      VERBATIM
      MAIN_DEPENDENCY ${PROJECT_RESOURCE_DIR}/${GRESOURCE_XML}
      DEPENDS
      ${PROJECT_RESOURCE_DIR}/sandbox.glade
      ${PROJECT_RESOURCE_DIR}/sandbox_child.glade
      ${CSS_OUTFILE}
      ${SPINNER_FILE}
)
add_custom_target(sandbox-resource DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})

set(MY_SOURCES
    src/main.c
    src/common_defs.h
    src/globals.h
    src/version.h
    src/utils/parse_args.c
    src/utils/parse_args.h
    src/utils/logging.c
    src/utils/logging.h
    src/utils/sys_interface.c
    src/utils/sys_interface.h
    src/controllers/app_ctrl.c
    src/controllers/app_ctrl.h
    src/models/model_device.c
    src/models/model_device.h
    src/models/model_workflow.c
    src/models/model_workflow.h
    src/models/app_model.c
    src/models/app_model.h
    src/views/view_builder.c
    src/views/view_builder.h
    src/views/view_styler.c
    src/views/view_styler.h
    src/views/root/view_app_root.c
    src/views/root/view_app_root.h
    src/views/misc_tab/view_app_child.c
    src/views/misc_tab/view_app_child.h
    src/views/button_box_tab/view_bound_toggles.c
    src/views/button_box_tab/view_bound_toggles.h
    src/models/model_samples.c
    src/models/model_samples.h
    src/views/samples_tab/view_samples.c
    src/views/samples_tab/view_samples.h
    src/views/root/view_msgout.h
    src/views/root/view_msgout.c
    src/views/view_utils.c
    src/views/view_utils.h
    src/controllers/ctrl_samples.c
    src/controllers/ctrl_samples.h
    src/views/view_wizard/view_wizard.c
    src/views/view_wizard/view_wizard.h
    src/models/search_worker.c src/models/search_worker.h)

include_directories(${PROJECT_SOURCE_DIR})
configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_SOURCE_DIR}/version.h")

# Executable
add_executable(${PROJECT_TARGET} ${MY_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})

target_include_directories(${PROJECT_TARGET} PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(${PROJECT_TARGET} ${GTK3_LIBRARIES})

add_custom_command(TARGET ${PROJECT_TARGET} PRE_BUILD COMMAND sassc -t expanded ${SCSS_SOURCE} ${CSS_OUTFILE})

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C} PROPERTIES GENERATED TRUE )
add_dependencies(${PROJECT_TARGET} sandbox-resource)
