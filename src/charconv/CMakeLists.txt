set(
	SGE_CHARCONV_BASE_FILES
	include/sge/charconv/char_type.hpp
	include/sge/charconv/charconv.hpp
	include/sge/charconv/const_raw_pointer.hpp
	include/sge/charconv/conversion_failed.hpp
	include/sge/charconv/conversion_status.hpp
	include/sge/charconv/convert.hpp
	include/sge/charconv/converter.hpp
	include/sge/charconv/converter_fwd.hpp
	include/sge/charconv/converter_unique_ptr.hpp
	include/sge/charconv/create_system.hpp
	include/sge/charconv/dest_encoding.hpp
	include/sge/charconv/encoding.hpp
	include/sge/charconv/exception.hpp
	include/sge/charconv/fcppt_string_to_utf8.hpp
	include/sge/charconv/input_range.hpp
	include/sge/charconv/output_range.hpp
	include/sge/charconv/raw_pointer.hpp
	include/sge/charconv/raw_value.hpp
	include/sge/charconv/source_encoding.hpp
	include/sge/charconv/string_type.hpp
	include/sge/charconv/system.hpp
	include/sge/charconv/system_fwd.hpp
	include/sge/charconv/system_scoped_ptr.hpp
	include/sge/charconv/system_unique_ptr.hpp
	include/sge/charconv/traits_type.hpp
	include/sge/charconv/unsupported_conversion.hpp
	include/sge/charconv/utf8_string.hpp
	include/sge/charconv/utf8_string_to_fcppt.hpp
	src/charconv/conversion_failed.cpp
	src/charconv/convert.cpp
	src/charconv/converter.cpp
	src/charconv/create_system.cpp
	src/charconv/exception.cpp
	src/charconv/fcppt_string_to_utf8.cpp
	src/charconv/include/sge/src/charconv/fcppt_is_utf8.hpp
	src/charconv/system.cpp
	src/charconv/unsupported_conversion.cpp
	src/charconv/utf8_string_to_fcppt.cpp
)

set(
	SGE_CHARCONV_ICONV_FILES
	src/charconv/backends/iconv/converter.cpp
	src/charconv/backends/iconv/encoding_to_string.cpp
	src/charconv/backends/iconv/system.cpp
	src/charconv/include/sge/src/charconv/backends/iconv/converter.hpp
	src/charconv/include/sge/src/charconv/backends/iconv/encoding_string.hpp
	src/charconv/include/sge/src/charconv/backends/iconv/encoding_to_string.hpp
	src/charconv/include/sge/src/charconv/backends/iconv/system.hpp
)

set(
	SGE_CHARCONV_WINDOWS_FILES
	src/charconv/backends/windows/converter.cpp
	src/charconv/backends/windows/system.cpp
	src/charconv/include/sge/src/charconv/backends/windows/converter.hpp
	src/charconv/include/sge/src/charconv/backends/windows/system.hpp
)

find_package(
	Iconv
)

if(
	ICONV_FOUND
)
	set(
		CHARCONV_BACKEND_DEFAULT
		"iconv"
	)
elseif(
	WIN32
)
	set(
		CHARCONV_BACKEND_DEFAULT
		"windows"
	)
endif()

set(
	CHARCONV_BACKEND
	"${CHARCONV_BACKEND_DEFAULT}"
	CACHE
	STRING
	"The charconv backend to use, possible values are: iconv, windows"
)

if(
	CHARCONV_BACKEND
	STREQUAL
	"iconv"
)
	set(
		SGE_CHARCONV_ICONV_BACKEND
		TRUE
	)

	set(
		SGE_CHARCONV_FILES
		"${SGE_CHARCONV_BASE_FILES};${SGE_CHARCONV_ICONV_FILES}"
	)

	include_directories(
		${FCPPT_UTILS_INCLUDE_SYSTEM}
		${ICONV_INCLUDE_DIRS}
	)

	if(
		NOT ICONV_IN_LIBC
	)
		set(
			SGE_CHARCONV_ADDITIONAL_DEPS
			"${ICONV_LIBRARIES}"
		)
	endif()
elseif(
	CHARCONV_BACKEND
	STREQUAL
	"windows"
)
	set(
		SGE_CHARCONV_WINDOWS_BACKEND
		TRUE
	)

	set(
		SGE_CHARCONV_FILES
		"${SGE_CHARCONV_BASE_FILES};${SGE_CHARCONV_WINDOWS_FILES}"
	)
else()
	message(
		ERROR
		"No charconv backend selected! See CHARCONV_BACKEND"
	)
endif()

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/backend.hpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/include/sge/charconv/backend.hpp"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}/include
)

add_sge_base_library(
	charconv
	"sgecore"
	"${Fcppt_core_LIBRARIES};${SGE_CHARCONV_ADDITIONAL_DEPS}"
	"sgecore"
	""
)
