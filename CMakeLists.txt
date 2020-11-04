cmake_minimum_required(VERSION 3.2)
project(LICV)
include_directories (Litecv/inc/Core)
include_directories (Litecv/inc/Imgproc)
aux_source_directory(./ DIR_MAIN)
set(LICV_MAIN ${DIR_MAIN})

add_compile_options(-std=c99)

aux_source_directory(./example/basicio DIR_EXP01)
set(LICV_EXP01 ${DIR_EXP01})
aux_source_directory(./example/painter DIR_EXP02)
set(LICV_EXP02 ${DIR_EXP02})


set(ARM OFF)

if(ARM)
aux_source_directory(./example/arm9 DIR_EXP03)
set(LICV_EXP03 ${DIR_EXP03})

else()
if (CMAKE_HOST_WIN32)
    set(WINDOWS ON)
elseif (CMAKE_HOST_APPLE)
    set(MACOS   ON)
elseif (CMAKE_HOST_UNIX)
    set(LINUX   ON)
endif ()
endif()


set(USE_JPEG   ON)
set(USE_PNG    ON)
add_subdirectory(Litecv)


add_executable(${PROJECT_NAME} ${LICV_MAIN})
target_link_libraries(${PROJECT_NAME} licvcore)
target_link_libraries(${PROJECT_NAME} licvimgproc)

add_executable(IO ${LICV_EXP01})
target_link_libraries(IO licvcore)

add_executable(Painter ${LICV_EXP02})
target_link_libraries(Painter licvcore)

if(ARM)
add_executable(display ${LICV_EXP03})
target_link_libraries(display licvcore)
endif(ARM)