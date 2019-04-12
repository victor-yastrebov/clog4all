cmake_minimum_required(VERSION 2.8)
project(LoggerImplTest)

set(gtest_disable_pthreads on)

# Add sub-directory that contains 'project(gtest)'.
add_subdirectory(${PROJECT_SOURCE_DIR}/3dparty/google_test/ ${CMAKE_BINARY_DIR}/LoggerImplTest/google_test/)
config_compiler_and_linker()

set(headers_test "")
set(sources_test "")
set(directories_test "")

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

message(STATUS "PROJECT_NAME: " ${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

include_directories(
   ${directories_logger}
   ${directories_mingw}
)

################################################################
# Fake-objects and other auxillary objects for organising tests
################################################################
add_subdirectory(${PROJECT_SOURCE_DIR}/stuff)

##############
# Unit-tests
##############
add_subdirectory(${PROJECT_SOURCE_DIR}/unitTests/)

###################################
# Source code of production classes
###################################
set(PRODUCTION_BIN_PARENT_DIR "${CMAKE_BINARY_DIR}/LoggerImplTest/ProductionBin/")

if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -std=gnu++0x -lpthread")
ELSEIF(APPLE)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -lpthread -framework Foundation")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x") # for gcc >= 4.7
ELSEIF(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -std=gnu++0x -lpthread -ldl -lXtst -lX11 -lXext")
endif()

add_definitions(
    # This flag should be setted for covering logger implementation
    # with unit-tests
   -DUNIT_TEST_LOGGER_IMPL
)

include_directories(${directories_test})

# Create executable file to run the tests
add_executable(${PROJECT_NAME}
   ${headers_logger}
   ${sources_logger}
   ${headers_mingw}
   ${headers_test}
   ${sources_test}
)

# link all the necessary libraries
target_link_libraries (${PROJECT_NAME} gtest gtest_main)