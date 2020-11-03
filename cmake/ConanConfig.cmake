# All taken from Jason Turner (https://github.com/lefticus) 
# retyped by me https://github.com/aljo242 for learning

macro(run_conan)
	file(COPY cmake/conan.cmake DESTINATION ${CMAKE_BINARY_DIR})

	if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
		message("conan.cmake file not properly copied to the build directory. Please manually copy the file from rt-research/cmake/ to your build dir.")
	endif()

	include(${CMAKE_BINARY_DIR}/conan.cmake)

	conan_cmake_run(
		REQUIRES
		${CONAN_EXTRA_REQUIRES}
		spdlog/1.7.0
		stb/20200203
		OPTIONS
		${CONAN_EXTRA_OPTIONS}
		BASIC_SETUP
		CMAKE_TARGETS
		BUILD
		missing
		)
endmacro()