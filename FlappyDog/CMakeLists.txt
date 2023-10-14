cmake_minimum_required( VERSION 3.27.6 FATAL_ERROR )
project( FlappyDog )

set( CMAKE_CXX_STANDARD 17 )

# Set directories
set( SOURCES_DIR  "src" )
set( RESOURCES_DIR  "${CMAKE_SOURCE_DIR}/Resources" )
set( INCLUDE_DIR  "include" )
set( EXTERNAL_DIR "external" )
set( BIN_DIR "${CMAKE_BINARY_DIR}/bin" )
set( LIB_DIR "${CMAKE_BINARY_DIR}/lib" )

# Set output files directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

# Add executable
add_executable( ${PROJECT_NAME} )

# Setup MSVC startup project
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

# Handle SDL main function on Windows
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    target_compile_definitions( ${PROJECT_NAME} PUBLIC SDL_MAIN_HANDLED )
endif()

# Set source files
target_sources( ${PROJECT_NAME} PRIVATE
    ${SOURCES_DIR}/main.cpp
    ${SOURCES_DIR}/Dog.cpp
    ${SOURCES_DIR}/Game.cpp
    ${SOURCES_DIR}/GameObject.cpp
    ${SOURCES_DIR}/Level.cpp
    ${SOURCES_DIR}/Pipe.cpp
    ${SOURCES_DIR}/ScoreWidget.cpp
)

# Include header files directory
target_include_directories( ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# SDL install
set( SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE )
set( SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_INSTALL OFF CACHE BOOL "" FORCE )

# Copy game resources to output directory post build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCES_DIR}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
)

# Configure SDL
set( SDL_TEST OFF CACHE BOOL "" FORCE )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Configure SDL_image
set( SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2IMAGE_VENDORED ON CACHE BOOL "" FORCE )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_image::SDL2_image>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Configure SDL_ttf
set( SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2TTF_VENDORED ON CACHE BOOL "" FORCE )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Configure SDL_mixer
set( SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE )
set( SDL2MIXER_FLAC OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MOD OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MP3 OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_MIDI OFF CACHE BOOL "" FORCE )
set( SDL2MIXER_OPUS OFF CACHE BOOL "" FORCE )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2_mixer::SDL2_mixer>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Include external subdirectories
add_subdirectory( ${EXTERNAL_DIR}/SDL )
add_subdirectory( ${EXTERNAL_DIR}/SDL_ttf )
add_subdirectory( ${EXTERNAL_DIR}/SDL_image )
add_subdirectory( ${EXTERNAL_DIR}/SDL_mixer )

# Link submodules libraries
target_link_libraries( ${PROJECT_NAME}
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)