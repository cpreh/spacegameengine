SET(
	SGE_ICONV_FILES
	src/plugins/iconv/converter.hpp
	src/plugins/iconv/encoding_string.hpp
	src/plugins/iconv/encoding_to_string.hpp
	src/plugins/iconv/src/converter.cpp
	src/plugins/iconv/src/encoding_to_string.cpp
	src/plugins/iconv/src/exports.cpp
	src/plugins/iconv/src/system.cpp
	src/plugins/iconv/system.hpp
)

INCLUDE_DIRECTORIES(
	${ICONV_INCLUDE_DIR}
)

IF(
	NOT ICONV_HAVE_POSIX
)
	SET(
		ICONV_LINK_LIBRARY
		${ICONV_LIBRARY}
	)
ENDIF()

ADD_SGE_PLUGIN(
	iconv
	"${ICONV_LINK_LIBRARY}"
)
