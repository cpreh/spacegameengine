SET(
	SGE_WINCONV_FILES
	src/plugins/winconv/include/sge/winconv/converter.hpp
	src/plugins/winconv/include/sge/winconv/system.hpp
	src/plugins/winconv/src/converter.cpp
	src/plugins/winconv/src/exports.cpp
	src/plugins/winconv/src/system.cpp
)

INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

ADD_SGE_PLUGIN(
	winconv
	"sgecharconv"
)
