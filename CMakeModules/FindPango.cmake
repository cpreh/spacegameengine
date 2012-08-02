include(
	FindPkgConfig
)

pkg_check_modules(
	PANGO
	${PANGO_FIND_REQUIRED}
	${PANGO_FIND_QUIETLY}
	pango
	pangoft2
)
