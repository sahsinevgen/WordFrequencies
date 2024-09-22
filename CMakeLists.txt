cmake_minimum_required(VERSION 3.5.1)

project(FrequencyMap LANGUAGES C CXX)

set(SUBDIRECTORIES src)
foreach(SUBDIR ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIR})
endforeach()