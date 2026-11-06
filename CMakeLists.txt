cmake_minimum_required(VERSION 3.16)
project(TheAngelEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(TheAngelEngine ${SOURCES})
target_include_directories(TheAngelEngine PRIVATE src)

# Use the plain main() entry point; no SDL2main link-order issues on MinGW.
target_compile_definitions(TheAngelEngine PRIVATE SDL_MAIN_HANDLED)

foreach(lib SDL2 SDL2_image SDL2_ttf SDL2_mixer)
  if(TARGET ${lib}::${lib})
    target_link_libraries(TheAngelEngine PRIVATE ${lib}::${lib})
  elseif(TARGET ${lib}::${lib}-static)
    target_link_libraries(TheAngelEngine PRIVATE ${lib}::${lib}-static)
  endif()
endforeach()

if(MSVC)
  target_compile_options(TheAngelEngine PRIVATE /W4)
else()
  target_compile_options(TheAngelEngine PRIVATE -Wall -Wextra)
endif()

# Copy assets/config next to the executable so relative paths work.
add_custom_command(TARGET TheAngelEngine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TheAngelEngine>/assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:TheAngelEngine>/config)
