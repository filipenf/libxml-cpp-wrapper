
cmake_minimum_required(VERSION 2.8)

project (xmlcppwrapper)

file(GLOB SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
file(GLOB HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

if(CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0 -Wall -fPIC")
    set( CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -DDEBUG")
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    /usr/local/include/libxml2/
)

add_library(
    ${CMAKE_PROJECT_NAME}
    ${SOURCE}
)


target_link_libraries(
    ${CMAKE_PROJECT_NAME}
	xml2
)

add_executable(
    writer_sample
    ${CMAKE_CURRENT_SOURCE_DIR}/example/writer.cpp
)
target_link_libraries(
    writer_sample
    ${CMAKE_PROJECT_NAME}
)

install(FILES ${HEADER} DESTINATION include) 
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib) 
