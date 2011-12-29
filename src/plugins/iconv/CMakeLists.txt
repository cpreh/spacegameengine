set(
	SGE_ICONV_FILES
	src/plugins/iconv/include/sge/iconv/converter.hpp
	src/plugins/iconv/include/sge/iconv/encoding_string.hpp
	src/plugins/iconv/include/sge/iconv/encoding_to_string.hpp
	src/plugins/iconv/include/sge/iconv/system.hpp
	src/plugins/iconv/src/converter.cpp
	src/plugins/iconv/src/encoding_to_string.cpp
	src/plugins/iconv/src/exports.cpp
	src/plugins/iconv/src/system.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include_directories(
	${ICONV_INCLUDE_DIR}
)

if(
	NOT ICONV_HAVE_POSIX
)
	set(
		ICONV_LINK_LIBRARY
		${ICONV_LIBRARY}
	)
endif()

add_sge_plugin(
	iconv
	"sgecharconv"
	"${ICONV_LINK_LIBRARY}"
)
