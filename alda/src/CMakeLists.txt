find_package(
	FcpptThreads
	REQUIRED
)

add_definitions(
	"${FcpptThreads_DEFINITIONS}"
)

set(
	ALDA_FILES
	alda/src/exception.cpp
	alda/src/include/alda/src/log_parameters.hpp
	alda/src/include/alda/src/net/server/detail/connection.hpp
	alda/src/include/alda/src/net/server/detail/object_impl.hpp
	alda/src/log.cpp
	alda/src/log_context.cpp
	alda/src/log_location.cpp
	alda/src/log_parameters.cpp
	alda/src/net/buffer/circular_receive/for_asio.cpp
	alda/src/net/buffer/circular_receive/object.cpp
	alda/src/net/buffer/circular_receive/part.cpp
	alda/src/net/buffer/circular_send/object.cpp
	alda/src/net/exception.cpp
	alda/src/net/io_service_wrapper.cpp
	alda/src/net/log_location.cpp
	alda/src/net/server/detail/connection.cpp
	alda/src/net/server/detail/object_impl.cpp
	alda/src/net/server/object.cpp
)

fcppt_generate_symbol_header(
	"ALDA_STATIC_LINK"
	"alda"
	"ALDA"
	"alda"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

function(
	add_alda_library
	VARIANT
)
	if(
		${VARIANT} STREQUAL "STATIC"
	)
		set(
			ALDA_LIB_NAME
			"alda_static"
		)
	else()
		set(
			ALDA_LIB_NAME
			"alda"
		)
	endif()

	fcppt_utils_append_source_dir_and_make_groups(
		"${ALDA_FILES}"
		ALDA_FILES_ABS
	)

	add_library(
		${ALDA_LIB_NAME}
		${VARIANT}
		${ALDA_FILES_ABS}
	)

	target_link_libraries(
		${ALDA_LIB_NAME}
		${Fcppt_core_LIBRARIES}
		${FcpptThreads_LIBRARIES}
		${Boost_SYSTEM_LIBRARY}
	)

	set_target_properties(
		${ALDA_LIB_NAME}
		PROPERTIES
		LINK_INTERFACE_LIBRARIES
		""
	)

	install(
		TARGETS
		${ALDA_LIB_NAME}
		DESTINATION
		${INSTALL_LIBRARY_DIR}
	)
endfunction()

function(
	alda_set_static_flags
	TARGETNAME
)
	if(
		ALDA_DEFAULT_LINK_TARGET
		STREQUAL
		"alda_static"
	)
		set_target_properties(
			${TARGETNAME}
			PROPERTIES
			COMPILE_DEFINITIONS
			"ALDA_STATIC_LINK"
		)
	endif()
endfunction()

if(
	ENABLE_SHARED
)
	add_alda_library(
		"SHARED"
	)
endif()

if(
	ENABLE_STATIC
)
	add_alda_library(
		"STATIC"
	)
endif()

install(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/alda/include/alda
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)

install(
	FILES
	${CMAKE_BINARY_DIR}/include/alda/symbol.hpp
	DESTINATION
	${INSTALL_INCLUDE_DIR}/alda
)
