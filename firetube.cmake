include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(FIRETUBE_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/src/firetube.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ftclient.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ftserver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ftutils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ftbase.cpp
)

#if system
IF (CMAKE_SYSTEM_NAME MATCHES "Windows") 
message(STATUS "Using firetube windows system source files.")
#windows:
set(FIRETUBE_SOURCE
    ${FIRETUBE_SOURCE}
    ${CMAKE_CURRENT_LIST_DIR}/src/windows/ftbase_win.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/windows/ftclient_win.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/windows/ftserver_win.cpp
)
ELSE () 
message(STATUS "Using firetube linux system source files.")
#linux
set(FIRETUBE_SOURCE
    ${FIRETUBE_SOURCE}
)
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Windows") 
