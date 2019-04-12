cmake_minimum_required(VERSION 2.8) 

set(headers_logger ${headers_logger} "${CMAKE_CURRENT_LIST_DIR}/logger.h")
set(sources_logger ${sources_logger} "${CMAKE_CURRENT_LIST_DIR}/logger.cpp")
set(headers_logger ${headers_logger} "${CMAKE_CURRENT_LIST_DIR}/logger_impl.h" PARENT_SCOPE)
set(sources_logger ${sources_logger} "${CMAKE_CURRENT_LIST_DIR}/logger_impl.cpp" PARENT_SCOPE)
set(directories_logger ${directories_logger} "${CMAKE_CURRENT_LIST_DIR}" PARENT_SCOPE)