pkg_check_modules(
	BULLET
	IMPORTED_TARGET
	bullet
)

get_target_property(
	INCLUDE_DIRS
	PkgConfig::BULLET
	INTERFACE_INCLUDE_DIRECTORIES
)

set_target_properties(
	PkgConfig::BULLET
	PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES
	""
)

target_include_directories(
	PkgConfig::BULLET
	SYSTEM
	INTERFACE
	${INCLUDE_DIRS}
)
