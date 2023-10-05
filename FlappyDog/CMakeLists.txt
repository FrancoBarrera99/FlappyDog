cmake_minimum_required(VERSION 3.0)
project(FlappyDog)

# Include SDL subdirectories
add_subdirectory(external/SDL)
add_subdirectory(external/SDL_ttf)
add_subdirectory(external/SDL_image)
add_subdirectory(external/SDL_mixer)

# Link project to SDL libraries
target_link_libraries(FlappyDog PRIVATE SDL SDL_ttf SDL_image SDL_mixer)
