project(ServerForMappers)

cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AMXConfig)
include(AddSAMPPlugin)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/amx
)

add_definitions(-DSAMPGDK_AMALGAMATION)

add_samp_plugin(ServerForMappers
  amxplugin.cpp
  sampgdk.c
  sampgdk.h
  ServerForMappers.def
  ServerForMappers.h
  ServerForMappers.cpp
  flymode.h
  flymode.cpp
  commands.h
  commands.cpp
)