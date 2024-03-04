cmake_minimum_required(VERSION 3.5)

file(GLOB SRCS ./*.h ./*.cpp)

add_library(Common STATIC ${SRCS})
add_library(lib::Common ALIAS Common)

target_include_directories(Common PUBLIC 
    ${CMAKE_SOURCE_DIR}/external/GLExtension/include
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}
)

get_target_property(LISTDIR Common INCLUDE_DIRECTORIES)

#foreach(dir ${LISTDIR})
#    message(STATUS "dirs : ${dir}")
#endforeach()


set_target_properties(Common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR}
)
