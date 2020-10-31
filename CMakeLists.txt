cmake_minimum_required(VERSION 3.2)
project(LICV)
include_directories (Litecv/inc/Core_inc)
aux_source_directory(./ DIR_MAIN)
set(LICV_MAIN ${DIR_MAIN})

if (CMAKE_HOST_WIN32)
    set(WINDOWS ON)
elseif (CMAKE_HOST_APPLE)
    set(MACOS   ON)
elseif (CMAKE_HOST_UNIX)
    set(LINUX   ON)
endif ()


set(USE_JPEG   ON)
set(USE_PNG    ON)
add_subdirectory(Litecv)


add_executable(${PROJECT_NAME} ${LICV_MAIN})
target_link_libraries(${PROJECT_NAME} licvcore)