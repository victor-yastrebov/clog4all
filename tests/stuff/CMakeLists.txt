cmake_minimum_required(VERSION 2.8)

#
# h-files
#
if(APPLE)
   set(headers_test ${headers_test} "${CMAKE_CURRENT_LIST_DIR}/logger_objc_test_ground.h")
endif()
set(headers_test ${headers_test} "${CMAKE_CURRENT_LIST_DIR}/logger_c_test_ground.h")
set(headers_test ${headers_test} "${CMAKE_CURRENT_LIST_DIR}/logger_cpp_test_ground.h" PARENT_SCOPE )

#
# source files
#
if(APPLE)
   set(sources_test ${sources_test} "${CMAKE_CURRENT_LIST_DIR}/logger_objc_test_ground.mm")
endif()
set(sources_test ${sources_test} "${CMAKE_CURRENT_LIST_DIR}/logger_c_test_ground.c")
set(sources_test ${sources_test} "${CMAKE_CURRENT_LIST_DIR}/logger_cpp_test_ground.cpp" PARENT_SCOPE)

set(directories_test ${directories_test} "${CMAKE_CURRENT_LIST_DIR}" PARENT_SCOPE)