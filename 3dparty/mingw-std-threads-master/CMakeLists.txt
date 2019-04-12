cmake_minimum_required(VERSION 2.8) 

set(headers_mingw ${headers_mingw} "${CMAKE_CURRENT_LIST_DIR}/mingw.mutex.h")
set(directories_mingw ${directories_mingw} "${CMAKE_CURRENT_LIST_DIR}" PARENT_SCOPE)