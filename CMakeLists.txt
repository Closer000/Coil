cmake_minimum_required(VERSION 3.25)

project(Coil LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

add_executable(Coil WIN32 "src/Code/coil.c" "resources/Snake.rc" "src/Code/food.c" "src/Code/textbutton.c" "src/Code/render.c" "src/Code/restart.c" "src/Code/rules.c" "src/Code/input.c" "src/Code/menus.c")

target_link_libraries(Coil PRIVATE raylib)

if(MSVC)
  target_link_options(Coil PRIVATE /ENTRY:mainCRTStartup)
  target_include_directories(Coil PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Head")
endif()

add_custom_command(TARGET Coil POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Coil> )
