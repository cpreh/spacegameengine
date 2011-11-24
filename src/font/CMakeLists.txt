SET(
	SGE_FONT_FILES
	include/sge/font/char_metric.hpp
	include/sge/font/char_metric_fwd.hpp
	include/sge/font/char_metric_ptr.hpp
	include/sge/font/char_not_available.hpp
	include/sge/font/char_type.hpp
	include/sge/font/const_image_view.hpp
	include/sge/font/dim.hpp
	include/sge/font/exception.hpp
	include/sge/font/font.hpp
	include/sge/font/image_view.hpp
	include/sge/font/metrics.hpp
	include/sge/font/metrics_fwd.hpp
	include/sge/font/metrics_ptr.hpp
	include/sge/font/plugin.hpp
	include/sge/font/pos.hpp
	include/sge/font/rect.hpp
	include/sge/font/size_type.hpp
	include/sge/font/symbol.hpp
	include/sge/font/system.hpp
	include/sge/font/system_fwd.hpp
	include/sge/font/system_ptr.hpp
	include/sge/font/unit.hpp
	src/font/char_metric.cpp
	src/font/char_not_available.cpp
	src/font/exception.cpp
	src/font/metrics.cpp
	src/font/plugin.cpp
	src/font/system.cpp
)

ADD_DEFINITIONS(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/src/plugin/include
)

ADD_SGE_BASE_LIBRARY(
	font
	"sgeplugin"
)
