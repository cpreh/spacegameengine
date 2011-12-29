set(
	SGE_WINCONV_FILES
	src/plugins/winconv/include/sge/winconv/converter.hpp
	src/plugins/winconv/include/sge/winconv/system.hpp
	src/plugins/winconv/src/converter.cpp
	src/plugins/winconv/src/exports.cpp
	src/plugins/winconv/src/system.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_sge_plugin(
	winconv
	"sgecharconv"
)
