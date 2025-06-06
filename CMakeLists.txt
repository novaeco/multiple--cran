cmake_minimum_required(VERSION 3.5)

# Enregistre les composants personnalisés situés 
# directement dans le dépôt (drivers, modules, ui)
set(EXTRA_COMPONENT_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/modules
    ${CMAKE_CURRENT_LIST_DIR}/ui
    ${CMAKE_CURRENT_LIST_DIR}/components)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(waveshare_touch)
