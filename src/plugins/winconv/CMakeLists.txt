SET(
	SGE_WINCONV_FILES
	src/plugins/winconv/converter.hpp
	src/plugins/winconv/src/converter.cpp
	src/plugins/winconv/src/exports.cpp
	src/plugins/winconv/src/system.cpp
	src/plugins/winconv/system.hpp
)

ADD_SGE_PLUGIN(
	winconv
	"sgecharconv"
)
