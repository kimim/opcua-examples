cmake_minimum_required(VERSION 3.1...3.12)
set(MYEXE simple-server)
project(${MYEXE} C)

find_package(open62541)

link_directories("c:/Program Files (x86)/open62541/lib")
include_directories("c:/Program Files (x86)/open62541/include")

link_libraries(open62541 ws2_32 Iphlpapi)

add_executable(${MYEXE} ${MYEXE}.c)
