cmake_minimum_required(VERSION 3.0)
project(FlappyDog)

# Include SDL subdirectories
add_subdirectory(SDL)
add_subdirectory(SDL_ttf)
add_subdirectory(SDL_image)
add_subdirectory(SDL_mixer)

# Link project to SDL libraries
target_link_libraries(FlappyDog PRIVATE SDL SDL_ttf SDL_image SDL_mixer)
