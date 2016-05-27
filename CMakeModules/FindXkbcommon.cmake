include(
	FindPkgConfig
)

pkg_check_modules(
	XKBCOMMON
	${XKBCOMMON_FIND_REQUIRED}
	${XKBCOMMON_FIND_QUIETLY}
	xkbcommon
)
