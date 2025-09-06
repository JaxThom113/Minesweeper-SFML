cmake_minimum_required(VERSION 3.16)
project(Minesweeper)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (try different versions)
find_package(SFML 2.5 REQUIRED COMPONENTS system window graphics network audio)

# Add your source files
add_executable(${PROJECT_NAME} 
    src/minesweeper.cpp
    src/minesweeper.h
    src/GameState.cpp
    src/GameState.h
    src/Tile.cpp
    src/Tile.h
    src/Button.cpp
    src/Button.h
    src/Toolbox.h
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} 
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-network 
    sfml-audio
)

# Copy images/ and boards/ to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/boards DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Platform-specific settings
if(WIN32)
    # Copy SFML DLLs to output directory on Windows
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-network>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Debug/Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
endif()