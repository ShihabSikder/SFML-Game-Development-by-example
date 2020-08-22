# Set a minimum CMake version
cmake_minimum_required(VERSION 3.1)

# Define project name
set(PROJECTNAME Snake)
project(${PROJECTNAME})

# Look for the SFML components
find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)

# Define a list of header directories
set(HEADERS
    "lib/"
)

# Include the header file directories
include_directories(${HEADERS})

# Define a list of our source files
set(SOURCES
    "src/main.cpp"
    "src/Snake.cpp"
    "src/World.cpp"
    "src/Window.cpp"
    "src/Game.cpp"
    "src/Textbox.cpp"
    "lib/Textbox.h"
    "lib/Snake.h"
    "lib/Game.h"
    "lib/Window.h"
    "lib/World.h"
)

# Set executable path to bin
set(EXECUTABLE_OUTPUT_PATH "../bin/")

# Define target executable based on the source files above
add_executable(${PROJECTNAME} ${SOURCES})

# Add the assets to the binary folder
file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/
    DESTINATION "../bin/assets/")

# Link executable to SFML and its dependencies
target_link_libraries(${PROJECTNAME} sfml-audio sfml-graphics sfml-window sfml-system)
