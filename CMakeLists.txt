cmake_minimum_required(VERSION 3.2)
project(LICV)
include_directories (Litecv/inc/Core)
include_directories (Litecv/inc/Image_proc)
aux_source_directory(./ DIR_MAIN)
set(LICV_MAIN ${DIR_MAIN})

aux_source_directory(./example/basicio DIR_EXP01)
set(LICV_EXP01 ${DIR_EXP01})
aux_source_directory(./example/painter DIR_EXP02)
set(LICV_EXP02 ${DIR_EXP02})

if (CMAKE_HOST_WIN32)
    set(WINDOWS ON)
elseif (CMAKE_HOST_APPLE)
    set(MACOS   ON)
elseif (CMAKE_HOST_UNIX)
    set(LINUX   ON)
endif ()


set(USE_JPEG   OFF)
set(USE_PNG    OFF)
add_subdirectory(Litecv)


add_executable(${PROJECT_NAME} ${LICV_MAIN})
target_link_libraries(${PROJECT_NAME} licvcore)

add_executable(IO ${LICV_EXP01})
target_link_libraries(IO licvcore)

add_executable(Painter ${LICV_EXP02})
target_link_libraries(Painter licvcore)
