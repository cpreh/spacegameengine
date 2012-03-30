include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(
	ENABLE_SHARED
)
	set(
		ALDA_DEFAULT_LINK_TARGET
		"alda"
	)
endif()

if(
	ENABLE_STATIC
)
	set(
		ALDA_DEFAULT_LINK_TARGET
		"alda_static"
	)
endif()

add_subdirectory(
	src
)

if(
	ENABLE_TEST
)
	add_subdirectory(
		tests
	)
endif()
