include(
	CheckIncludeFile
)

check_include_file(
	linux/inotify.h
	HAVE_INOTIFY_HEADER
)

check_include_file(
	linux/input.h
	HAVE_INPUT_HEADER
)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	EVDEV
	DEFAULT_MSG
	HAVE_INOTIFY_HEADER
	HAVE_INPUT_HEADER
)

mark_as_advanced(
	HAVE_INOTIFY_HEADER
	HAVE_INPUT_HEADER
)
