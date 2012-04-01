if(
	Alda_FIND_QUIETLY
)
	set(
		ALDA_FIND_OPTIONS
		"QUIET"
	)
endif()

if(
	Alda_FIND_REQUIRED
)
	set(
		ALDA_FIND_OPTIONS
		"REQUIRED"
	)
endif()

# TODO: Find dependencies

find_path(
	Alda_INCLUDE_DIR
	NAMES awl/config.hpp
	HINTS ${ALDA_INCLUDEDIR}
)

# TODO: Search for the static library as well

find_library(
	Alda_LIBRARY
	NAMES alda
	HINTS ${ALDA_LIBRARYDIR}
)

# TODO: Include Boost, fcppt, sge, etc.
set(
	Alda_INCLUDE_DIRS
	"${Alda_INCLUDE_DIR}"
)

# TODO: Include what is needed here
set(
	Alda_LIBRARIES
	"${Alda_LIBRARY}"
)
