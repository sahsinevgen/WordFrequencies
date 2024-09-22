message("Processing src directory...")

set(SUBDIRECTORIES solutions)
foreach(SUBDIR ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIR})
endforeach()

add_executable(freq main.cpp)
target_link_libraries(freq PRIVATE solutions)