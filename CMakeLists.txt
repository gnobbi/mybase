cmake_minimum_required(VERSION 2.8)

# mybase
set(exe_name mybase)

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
message(warning ${SUBDIRS})
FOREACH(subdir ${SUBDIRS})
	message(warning ${subdir})
	file(GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.cpp)
	source_group(${subdir} srcs)
ENDFOREACH()

file(GLOB_RECURSE exe_srcs src/*.cpp)

add_library(${exe_name} ${exe_srcs})
set_target_properties (${exe_name} PROPERTIES FOLDER lib)

source_group(xml )

include_directories(include)
include_directories(src)
include_directories(src/xml)

