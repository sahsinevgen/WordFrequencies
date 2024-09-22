message("Processing solutions directory...")

# Add subdirectories.
set(SUBDIRECTORIES std_solution)
foreach(SUBDIR ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIR})
endforeach()

# Create executable.
# add_executable(main main.cpp)

add_library(solutions
	solutions.cpp
)

target_link_libraries(solutions PRIVATE
    std_solution
)
