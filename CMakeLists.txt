cmake_minimum_required(VERSION 3.14)
project(Traffic_Remover CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
	${SOURCES}
	src/main.cpp
	src/remover.cpp
	)

set(HEADERS
	${HEADERS}
	include/remover.hpp
	)

add_executable(Traffic_Remover ${SOURCES} ${HEADERS})

# Qt
find_package(Qt6 COMPONENTS Core REQUIRED)

target_include_directories(Traffic_Remover PRIVATE "${ROOT}/include")
target_link_libraries(Traffic_Remover PRIVATE Qt6::Core)

# VS stuff
set_property(DIRECTORY ${ROOT} PROPERTY VS_STARTUP_PROJECT Traffic_Remover)
source_group(TREE ${ROOT} FILES ${SOURCES} ${HEADERS})