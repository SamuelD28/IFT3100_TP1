cmake_minimum_required(VERSION 3.28.3)

# CPP requirements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(app VERSION 1.0.0)
add_executable(app)

# Libraries linking
add_subdirectory(pkg/glad)
target_link_libraries(app glad)

find_package(glfw3 REQUIRED CONFIG)
target_link_libraries(app glfw)

file(COPY ${CMAKE_SOURCE_DIR}/bin DESTINATION ${CMAKE_BINARY_DIR})

target_sources(app PRIVATE 
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/shader.cpp
	${CMAKE_SOURCE_DIR}/src/shape.cpp
	${CMAKE_SOURCE_DIR}/src/application.cpp
)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)