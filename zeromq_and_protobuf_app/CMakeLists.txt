cmake_minimum_required(VERSION 3.5)
project(zeromq_protobuf)
set(zeromq_protobuf_MAJOR_VERSION 0)
set(zeromq_protobuf_MINOR_VERSION 1)
set(zeromq_protobuf_PATCH_VERSION 0)
set(zeromq_protobuf_VERSION
  ${zeromq_protobuf_MAJOR_VERSION}.${zeromq_protobuf_MINOR_VERSION}.${zeromq_protobuf_PATCH_VERSION})
set (CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

# find the protobuf compiler and libraries
find_package(Protobuf REQUIRED)

# check if protobuf was found
if(PROTOBUF_FOUND)
    message ("protobuf found")
else()
    message (FATAL_ERROR "Cannot find Protobuf")
endif()

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "src/message.proto")
# Print path to generated files
message ("PROTO_SRCS = ${PROTO_SRCS}")
message ("PROTO_HDRS = ${PROTO_HDRS}")

add_compile_options(-W -Wall -Werror)

find_package(Boost COMPONENTS regex)

include_directories(
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable (req src/req.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(req PRIVATE zmq ${PROTOBUF_LIBRARIES})

add_executable (rep src/rep.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(rep PRIVATE zmq ${PROTOBUF_LIBRARIES})

