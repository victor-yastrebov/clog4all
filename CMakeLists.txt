cmake_minimum_required(VERSION 2.8)

# generate test project using Google Test framework
# set this option to OFF in order not to generate test project
option(gen_test_project "Build all tests." ON)

project(LoggerImpl)

# variables are modified inside child
# CMakeLists.txt using PARENT_SCOPE qualifier
set(header_logger "")
set(sources_logger "")
set(directories_logger "")

set(header_mingw "")
set(directories_mingw "")

# pthread - for std::mutex support
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++0x")

message("flags are: " ${CMAKE_CXX_FLAGS})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/logger/)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3dparty/mingw-std-threads-master/)

include_directories(
   ${directories_logger}
   ${directories_mingw}
)

add_definitions(
    # This compile directive should be setted if you wish not to free allocated
    # memory for logger singleton by your application. It can be usefull if you
    # wish to log from destructors of global/static objects.
    # Usually operation systems perform freeing resources that were managed by
    # the finished process. However for using this flag you should check your OS
    # specification in oder to avoid memory leak
   -DDELETE_SINGLETON_OBJ_BY_OS
)

add_executable(${PROJECT_NAME}
   ${header_logger}
   ${sources_logger}
   ${headers_mingw}
   "main.cpp"
)

if(gen_test_project)
    set(PROJECT LoggerImplTest)
    project (${PROJECT})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests ${CMAKE_BINARY_DIR}/LoggerImplTest)
endif()
