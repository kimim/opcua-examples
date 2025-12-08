cmake_minimum_required(VERSION 3.1...3.12)
set(MYEXE pubsub-publish)
project(${MYEXE} C)

include(../../common/c/common.cmake)

# see https://cmake.org/cmake/help/latest/command/add_subdirectory.html
# If it is a relative path, it will be evaluated with respect to the current output directory
add_subdirectory(../../common/c/open62541 open62541)

if(WIN32)
  #find_package(open62541)
  #link_directories("c:/Program Files (x86)/open62541/lib")
  #include_directories("c:/Program Files (x86)/open62541/include")
  link_libraries(open62541 ws2_32 Iphlpapi)
elseif(UNIX)
  link_libraries(open62541)
endif()

add_executable(${MYEXE} ${MYEXE}.c)
