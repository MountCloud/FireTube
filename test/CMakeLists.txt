cmake_minimum_required(VERSION 3.20)

project(firetube_test)

set(EXE_NAME "firetube_test")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS " -static -pthread")


if(MSVC)

    #管理员权限
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /level='requireAdministrator' /uiAccess='false'")

    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} "/MTd")
    
    set(COMPILE_IGNORE_WARNING
        /wd4828
    )

    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
        $<$<C_COMPILER_ID:MSVC>:/utf-8>
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        ${COMPILE_IGNORE_WARNING}
    )
endif()

#项目根目录
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_WIN_DIR ${PROJECT_SOURCE_DIR}/src/win)
set(SRC_LINUX_DIR ${PROJECT_SOURCE_DIR}/src/linux)

#生成目录
set(LIBRARY_OUTPUT_PATH ${BIN_DIR})
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

get_filename_component(DIR_ONE_ABOVE ../ ABSOLUTE) 

message(STATUS "DIR_ONE_ABOVE : ${DIR_ONE_ABOVE}")

include_directories(${INCLUDE_DIR})

#include firetube cmake
include(${DIR_ONE_ABOVE}/firetube.cmake)

#exe配置
add_executable(${EXE_NAME}_imput_msg_client
    ${FIRETUBE_SOURCE}
    ${PROJECT_SOURCE_DIR}/test_input_msg_client.cpp
)

add_executable(${EXE_NAME}_imput_msg_server
    ${FIRETUBE_SOURCE}
    ${PROJECT_SOURCE_DIR}/test_input_msg_server.cpp
)

#exe配置
add_executable(${EXE_NAME}_multithreading_bigdata_client
    ${FIRETUBE_SOURCE}
    ${PROJECT_SOURCE_DIR}/test_multithreading_bigdata_client.cpp
)

add_executable(${EXE_NAME}_multithreading_bigdata_server
    ${FIRETUBE_SOURCE}
    ${PROJECT_SOURCE_DIR}/test_multithreading_bigdata_server.cpp
)

add_executable(${EXE_NAME}_multithreading_bigdata_check
    ${FIRETUBE_SOURCE}
    ${PROJECT_SOURCE_DIR}/test_multithreading_bigdata_check.cpp
)

# target_include_directories(${EXE_NAME}
#     PRIVATE
#         ${COMMON_DIR}
#         ${INCLUDE_DIR}
# )

#target_link_libraries(${EXE_NAME} -static-libgcc -static-libstdc++)
