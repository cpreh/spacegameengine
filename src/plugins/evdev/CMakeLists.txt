set(
	SGE_EVDEV_FILES
	src/plugins/evdev/include/sge/evdev/system.hpp
	src/plugins/evdev/src/exports.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_sge_plugin(
	evdev
	"sgeinput;sgelog;sgeplugin"
	""
)
