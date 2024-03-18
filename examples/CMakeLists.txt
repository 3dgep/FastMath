cmake_minimum_required(VERSION 3.22.1) # The version of CMake used when creating this project.

add_subdirectory(01-Vectors)

set_target_properties(
	01-Vectors
	PROPERTIES
		FOLDER Examples
)

# Set the startup project.
set_directory_properties( PROPERTIES 
	VS_STARTUP_PROJECT 01-Vectors
)
