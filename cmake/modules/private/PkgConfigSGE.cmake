macro(
	pkg_check_modules_sge
	VAR_NAME
)
	pkg_check_modules(
		${VAR_NAME}
		IMPORTED_TARGET
		${ARGN}
	)

	if(
		${VAR_NAME}_FOUND
	)
		get_target_property(
			INCLUDE_DIRS
			PkgConfig::${VAR_NAME}
			INTERFACE_INCLUDE_DIRECTORIES
		)

		set_target_properties(
			PkgConfig::${VAR_NAME}
			PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES
			""
		)

		target_include_directories(
			PkgConfig::${VAR_NAME}
			SYSTEM
			INTERFACE
			${INCLUDE_DIRS}
		)
	endif()
endmacro()
