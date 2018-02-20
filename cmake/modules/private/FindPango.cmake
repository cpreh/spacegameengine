include(
	FindPkgConfig
)

pkg_check_modules(
	PANGO
	${PANGO_FIND_REQUIRED}
	${PANGO_FIND_QUIETLY}
	IMPORTED_TARGET
	pango
	pangoft2
	fontconfig
)
