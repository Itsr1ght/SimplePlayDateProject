cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if(NOT ${ENVSDK} STREQUAL "")
  # Convert path from Windows
  file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
  execute_process(
    COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
    COMMAND head -n 1
    COMMAND cut -c9-
    OUTPUT_VARIABLE SDK
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if(NOT EXISTS ${SDK})
  message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
  return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

# Game Name Customization
set(PLAYDATE_GAME_NAME FirstGame)
set(PLAYDATE_GAME_DEVICE FirstGame_DEVICE)

project(${PLAYDATE_GAME_NAME} C ASM)

file(GLOB IMAGES
  "Source/images/*"
)

if(TOOLCHAIN STREQUAL "armgcc")
  add_executable(${PLAYDATE_GAME_DEVICE} main.c game.c)
else()
  add_library(${PLAYDATE_GAME_NAME} SHARED Source/main.c ${IMAGES})
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)
