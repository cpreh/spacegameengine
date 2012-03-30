include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(
	ENABLE_TEST
)
	add_subdirectory(
		tests
	)
endif()

install(
	DIRECTORY
	${CMAKE_CURRENT_SOURCE_DIR}/include/alda
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)
