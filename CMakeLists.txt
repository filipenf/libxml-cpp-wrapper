
cmake_minimum_required(VERSION 2.8)

project (xmlcppwrapper)

file(GLOB SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
file(GLOB HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

include_directories(
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

install(FILES ${HEADER} DESTINATION include) 
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib) 
