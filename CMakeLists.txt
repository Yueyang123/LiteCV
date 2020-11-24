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
aux_source_directory(./example/conv   DIR_EXP04)
set(LICV_EXP04 ${DIR_EXP04})
aux_source_directory(./example/canny   DIR_EXP05)
set(LICV_EXP05 ${DIR_EXP05})
aux_source_directory(./example/Hist   DIR_EXP06)
set(LICV_EXP06 ${DIR_EXP06})

set(ARM OFF)

if(ARM)
   message(ARM)
else()
    if (CMAKE_HOST_WIN32)
         message(WINDOWS)
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

add_executable(smooth ${LICV_EXP04})
target_link_libraries(smooth licvcore)
target_link_libraries(smooth licvimgproc)

add_executable(canny ${LICV_EXP05})
target_link_libraries(canny licvcore)
target_link_libraries(canny licvimgproc)

add_executable(Hist ${LICV_EXP06})
target_link_libraries(Hist licvcore)
target_link_libraries(Hist licvimgproc)