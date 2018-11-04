cmake_minimum_required(VERSION 3.8)
project(bootloader C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(EFI REQUIRED)
add_library(efiboot SHARED main.c data.c util.c)

target_link_libraries(efiboot efi)
create_efi_image(efiboot boot)
