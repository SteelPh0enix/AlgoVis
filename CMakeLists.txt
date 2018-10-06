cmake_minimum_required(VERSION 3.10)

# C++ settings
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O2 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Wextra -Wpedantic")

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Set the type of build" FORCE)
endif()

project(AlgoVis)

# Per build type settings
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(SFML_LIBS sfml-system-d sfml-window-d sfml-graphics-d)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(SFML_LIBS sfml-system sfml-window sfml-graphics)
    if (WIN32)
        set(SFML_LIBS ${SFML_LIBS} sfml-main)
    endif()
endif()

# Find CMake
if(WIN32)
    set(SFML_INCLUDE_DIR "" CACHE PATH "SFML include directory")
    set(SFML_LIBRARY_DIR "" CACHE PATH "SFML libraries directory")
else()
    set(SFML_INCLUDE_DIR "/usr/include" CACHE PATH "SFML include directory")
    set(SFML_LIBRARY_DIR "/usr/lib" CACHE PATH "SFML libraries directory")
endif()

# Include 3rd party libs into the project
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Set all the source files (glob is evil)
set(SOURCE_FILES_LIST main.cpp HUD.cpp Settings.cpp Visualizator.cpp)

if (WIN32 AND CMAKE_BUILD_TYPE MATCHES Release)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES_LIST})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES_LIST})
endif()

# Link libraries to executable
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION ".")
install(FILES Assets/ShareTechMono-Regular.ttf DESTINATION "Assets/")
install(FILES settings.json DESTINATION ".")
