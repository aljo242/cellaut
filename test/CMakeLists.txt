#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
MESSAGE("SETTING UP TESTS")

add_executable(test_cartcoord cartcoord.cpp ../src/VMesh.cpp)


foreach(TARGET_NAME
	IN ITEMS
		test_cartcoord
		
)

	target_link_libraries(${TARGET_NAME} PUBLIC
		${EXTRA_LIBS}
	)

	target_include_directories(${TARGET_NAME} PUBLIC
		${PROJECT_BINARY_DIR}
	)
	
endforeach()


target_link_libraries(test_cartcoord PUBLIC
	${EXTRA_LIBS}
)

target_include_directories(test_cartcoord PUBLIC
	${PROJECT_BINARY_DIR}
)

add_test(NAME cartcoord COMMAND test_cartcoord
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)