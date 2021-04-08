cmake_minimum_required(VERSION 3.5)
project(read_protobuf)
set(read_protobuf_MAJOR_VERSION 0)
set(read_protobuf_MINOR_VERSION 1)
set(read_protobuf_PATCH_VERSION 0)
set(read_protobuf_VERSION
  ${read_protobuf_MAJOR_VERSION}.${read_protobuf_MINOR_VERSION}.${read_protobuf_PATCH_VERSION})
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

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS "src/common.proto" "src/log_model.proto")
     
# Print path to generated files
message ("PROTO_SRCS = ${PROTO_SRCS}")
message ("PROTO_HDRS = ${PROTO_HDRS}")

add_compile_options(-W -Wall -Werror)

include_directories(
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable (main src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(main PRIVATE ${PROTOBUF_LIBRARIES})


