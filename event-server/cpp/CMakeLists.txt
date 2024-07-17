cmake_minimum_required(VERSION 3.12)

set(MYEXE event-server)

project(
  ${MYEXE}
  VERSION 0.13.0
  DESCRIPTION "simple server based on open62541pp"
  HOMEPAGE_URL "https://github.com/kimim/opcua-examples"
  LANGUAGES CXX
)

# set c++ standard explicitly, compile feature "cxx_std_17" does not set -std=c++17 compile flag
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(../../common/cpp/open62541pp open62541pp)

if(WIN32)
  #find_package(open62541)
  #link_directories("c:/Program Files (x86)/open62541/lib")
  #include_directories("c:/Program Files (x86)/open62541/include")
  link_libraries(open62541pp ws2_32 Iphlpapi)
elseif(UNIX)
  link_libraries(open62541pp)
endif()

add_executable(${MYEXE} ${MYEXE}.cpp)
