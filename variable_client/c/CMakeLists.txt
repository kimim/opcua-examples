cmake_minimum_required(VERSION 3.1...3.12)
set(MYEXE variable-client)

project(
  ${MYEXE}
  VERSION 0.13.0
  DESCRIPTION "variable client based on open62541"
  HOMEPAGE_URL "https://github.com/kimim/opcua-examples"
  LANGUAGES C
)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

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
