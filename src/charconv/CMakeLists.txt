set(
	SGE_CHARCONV_FILES
	include/sge/charconv/charconv.hpp
	include/sge/charconv/const_raw_pointer.hpp
	include/sge/charconv/conversion_failed.hpp
	include/sge/charconv/conversion_status.hpp
	include/sge/charconv/convert.hpp
	include/sge/charconv/converter.hpp
	include/sge/charconv/converter_fwd.hpp
	include/sge/charconv/converter_ptr.hpp
	include/sge/charconv/dest_encoding.hpp
	include/sge/charconv/encoding.hpp
	include/sge/charconv/exception.hpp
	include/sge/charconv/input_range.hpp
	include/sge/charconv/output_range.hpp
	include/sge/charconv/plugin.hpp
	include/sge/charconv/plugin_ptr.hpp
	include/sge/charconv/raw_pointer.hpp
	include/sge/charconv/raw_value.hpp
	include/sge/charconv/source_encoding.hpp
	include/sge/charconv/string_type.hpp
	include/sge/charconv/symbol.hpp
	include/sge/charconv/system.hpp
	include/sge/charconv/system_fwd.hpp
	include/sge/charconv/system_ptr.hpp
	include/sge/charconv/unsupported_conversion.hpp
	src/charconv/conversion_failed.cpp
	src/charconv/convert.cpp
	src/charconv/converter.cpp
	src/charconv/exception.cpp
	src/charconv/plugin.cpp
	src/charconv/system.cpp
	src/charconv/unsupported_conversion.cpp
)

add_definitions(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)


include_directories(
	${CMAKE_SOURCE_DIR}/src/plugin/include
)

add_sge_base_library(
	charconv
	"sgecore;sgeplugin"
	""
	"sgecore"
	""
)
