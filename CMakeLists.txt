cmake_minimum_required(VERSION 3.20)
project(snake)

set(CMAKE_CXX_STANDARD 14)

add_executable(snake main.cpp snake.cpp snake.h)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

#Specific Windows dependencies
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 gdi32 winmm)
endif(WIN32)