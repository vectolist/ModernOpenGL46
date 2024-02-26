cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)


project(ModernGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(TITLES
    01-window
)

set(01-window
    01-draw
)

set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

configure_file(root.h.in ./config/root.h)
include_directories(${CMAKE_BINARY_DIR}/config)
link_directories(${CMAKE_SOURCE_DIR}/lib)

foreach(TITLE ${TITLES})
    foreach(EXAM ${${TITLE}})
        set(CUR_DIR src/${TITLE}/${EXAM})
        message(STATUS "title : ${CUR_DIR}")
        file(GLOB SRCS
            ${CUR_DIR}/*.h
            ${CUR_DIR}/*.cpp
            ${CUR_DIR}/*.glsl
        )
        set(NAME "${TITLE}-${EXAM}")
        add_executable(${NAME} ${SRCS})
        if(MSVC)
            target_compile_options(${NAME} PRIVATE /std:c++17 /MP)
            target_link_options(${NAME} PUBLIC /ignore:4099)
        endif(MSVC)
        set_target_properties(${NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/${EXAM}
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/${EXAM}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/${EXAM}
            VS_DEBUGGER_WORKING_DIRECTORY ${BIN_DIR}/${EXAM}
            #IMPORTED_LOCATION
        )
        message(STATUS "project name :  ${NAME}")
        file(GLOB SHADERS 
            ${CUR_DIR}/*.glsl
            ${CUR_DIR}/*.vs
            ${CUR_DIR}/*.ps
            ${CUR_DIR}/*.fs
            ${CUR_DIR}/*.gs
            ${CUR_DIR}/*.cs
            ${CUR_DIR}/*.hs
            ${CUR_DIR}/*.ts
        )

        foreach(SHADER ${SHADERS})
            add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADERS} $<TARGET_FILE_DIR:${NAME}>)    
        endforeach(SHADER ${SHADERS}) 
    endforeach(EXAM)
    
endforeach(TITLE)

include_directories()

