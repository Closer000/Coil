cmake_minimum_required(VERSION 3.25)

project(Coil LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib CONFIG REQUIRED)

add_executable(Coil WIN32 "src/Code/coil.c" "resources/Snake.rc" "src/Code/food.c" "src/Code/textbutton.c" "src/Code/render.c" "src/Code/restart.c" "src/Code/rules.c" "src/Code/input.c" "src/Code/menus.c" "src/Code/sound.c")

target_link_libraries(Coil PRIVATE raylib)

if(MSVC)
  target_link_options(Coil PRIVATE /ENTRY:mainCRTStartup)
  target_compile_options(Coil PRIVATE /utf-8)
  target_include_directories(Coil PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Head")
endif()

add_custom_command(TARGET Coil POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Coil> )

if(DEFINED ENV{COIL_VCPKG_ROOT})
  add_custom_command(TARGET Coil POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "$ENV{COIL_VCPKG_ROOT}/installed/x64-windows/bin/raylib.dll"
      "$ENV{COIL_VCPKG_ROOT}/installed/x64-windows/bin/glfw3.dll"
      "$<TARGET_FILE_DIR:Coil>")
endif()
