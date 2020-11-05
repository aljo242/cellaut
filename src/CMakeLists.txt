add_executable(main
	main.cpp "Renderer.h" "Renderer.cpp"  "ConwayGame.h" "ConwayGame.cpp" "Log.h" "Timer.h" "Timer.cpp" "VMesh.h" "VMesh.cpp")

target_link_libraries(main PUBLIC
		${EXTRA_LIBS}
	)

target_include_directories(main PUBLIC
	${PROJECT_BINARY_DIR}
	)