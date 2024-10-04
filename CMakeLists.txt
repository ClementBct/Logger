cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE Release)
set(LIB_FOLDER Logger)
project(logger VERSION 0.1 LANGUAGES CXX)


add_library(${PROJECT_NAME}_shared SHARED 
${LIB_FOLDER}/sources/Logger.cpp
)
add_library(${PROJECT_NAME}_static STATIC 
${LIB_FOLDER}/sources/Logger.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${LIB_FOLDER}/include)

set_target_properties(${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}_shared
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

set_target_properties(${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}_static
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

#Copy include in lib folder 
file(COPY ${LIB_FOLDER}/include DESTINATION ${CMAKE_BINARY_DIR}/lib)
