project(Emulator)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

#file(GLOB language_SRC
#    "Language/*.h"
#    "Language/*.cpp"
#)

#file(GLOB_RECURSE language_cities_SRC
#    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/Language/Cities/*.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/Language/Cities/*.cpp
#)

file(GLOB emu_SRC ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.h)

add_executable(${chip8_EXEC}
    ${emu_SRC}
)

TARGET_LINK_LIBRARIES(${chip8_EXEC}
    ${SDL2_LIBRARY}
    ${SDL2_GFX_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

