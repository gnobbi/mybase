cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE external_header include/*.h)
file(GLOB_RECURSE internal_header src/*.h)
file(GLOB_RECURSE srcs src/*.cpp)
ADD_MSVC_PRECOMPILED_HEADER(${CMAKE_CURRENT_SOURCE_DIR}/src/precompiled.cpp "${srcs}")

add_library(${exe_name} ${external_header} ${internal_header} ${srcs})

# source filters
file(GLOB internal_header ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
source_group(source FILES ${internal_header})
source_group(source FILES ${srcs})
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
FOREACH(subdir ${SUBDIRS})
	file(GLOB_RECURSE internal_module_header ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.h)
	file(GLOB_RECURSE module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.cpp)
	source_group(source\\${subdir} FILES ${internal_module_header})
	source_group(source\\${subdir} FILES ${module_srcs})
ENDFOREACH()

# include filter
file(GLOB external_header ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
source_group(include FILES ${external_header})
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
FOREACH(subdir ${SUBDIRS})
	file(GLOB_RECURSE external_module_header ${CMAKE_CURRENT_SOURCE_DIR}/include/${subdir}/*.h)
	source_group(include\\${subdir} FILES ${external_module_header})
ENDFOREACH()

set_target_properties(${exe_name} PROPERTIES COMPILE_DEFINITIONS "COMPILING_DLL=1")
set_target_properties (${exe_name} PROPERTIES FOLDER lib)
include_directories(include)
include_directories(src)


# tests
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/test/UnitTests)
FOREACH(subdir ${SUBDIRS})
	set(exe_name ${subdir})
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test/UnitTests/${subdir})
ENDFOREACH()
