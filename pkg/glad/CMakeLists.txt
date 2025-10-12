cmake_minimum_required(VERSION 3.28.3)
project(glad VERSION 1.0.1 DESCRIPTION "glad mapper file")
include(GNUInstallDirs)
add_library(glad SHARED src/glad.cpp)

set_target_properties(
	glad PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
	PUBLIC_HEADER include/glad.h
)

target_include_directories(glad PUBLIC include)

install(
	TARGETS glad
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)