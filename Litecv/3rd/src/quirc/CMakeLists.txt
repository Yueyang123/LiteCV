cmake_minimum_required(VERSION 3.2)

add_compile_options(-O3 -Wall -fPIC)

include_directories(lib)
aux_source_directory(./lib QUIRC_SRC)

SET(QUIRC ${QUIRC_SRC})
add_library(quirc STATIC  ${QUIRC})