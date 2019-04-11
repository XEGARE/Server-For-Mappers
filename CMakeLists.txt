project (ServerForMappers)

cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(s
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdk
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdk/amx
)

add_definitions(-DSAMPGDK_AMALGAMATION)

add_samp_plugin(${PROJECT_NAME}
  lib/amxplugin.cpp
  lib/sampgdk.c
  lib/sampgdk.h
  src/ServerForMappers.def
  src/ServerForMappers.h
  src/ServerForMappers.cpp
  src/flymode.h
  src/flymode.cpp
  src/commands.h
  src/commands.cpp
)