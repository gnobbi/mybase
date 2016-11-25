cmake_minimum_required(VERSION 2.8)

# mybase
set(exe_name mybase)
message("   Start " ${exe_name})

file(GLOB_RECURSE external_header include/*.h)
file(GLOB_RECURSE internal_header src/*.h)
file(GLOB_RECURSE srcs src/*.cpp)
source_group(include FILES ${external_header})
add_library(${exe_name} ${external_header} ${internal_header} ${srcs})

# source filters
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
FOREACH(subdir ${SUBDIRS})
	file(GLOB_RECURSE module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.cpp)
	file(GLOB_RECURSE module_header ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/*.h)
	source_group(${subdir} FILES ${module_srcs})
	source_group(${subdir} FILES ${module_header})
ENDFOREACH()

set_target_properties (${exe_name} PROPERTIES FOLDER lib)
include_directories(include)
include_directories(src)

message("   End " ${exe_name})

