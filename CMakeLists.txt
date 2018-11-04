cmake_minimum_required(VERSION 3.8)
project(mos C CXX ASM)

# VERSION INFO (currently uses gitcommit + version)
# CHANGE ME: Set to current version as str and as int
set(MOS_VERSION_INT 0)
set(MOS_VERSION_STR \"0.0.0\")

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE MOS_VERSION_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE MOS_VERSION_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
	${CMAKE_SOURCE_DIR}/common/version.h.in
	${CMAKE_BINARY_DIR}/common/version.h
)

include_directories(${CMAKE_BINARY_DIR}/common)

add_subdirectory(bootloader)
