# - Find VORBIS
# Find the native VORBIS headers and libraries.
#
#  Input variables:
#
#  VORBIS_ROOT         - Hint where to find vorbis
#  OGG_ROOT            - Hint where to find ogg
#  VORBIS_INCLUDE_DIR  - The include dir for vorbis
#  VORBIS_LIBRARY      - The vorbis library
#  VORBIS_FILE_LIBRARY - The vorbisfile library
#  OGG_INCLUDE_DIR     - The include dir for ogg
#  OGG_LIBRARY         - The ogg library
#

FIND_PATH(
	VORBIS_INCLUDE_DIR
	NAMES vorbis/vorbisfile.h
	HINTS "${VORBIS_ROOT}"/include
)

FIND_PATH(
	OGG_INCLUDE_DIR
	NAMES ogg/ogg.h
	HINTS "${OGG_ROOT}"/include
)

FIND_LIBRARY(
	VORBIS_LIBRARY
	NAMES vorbis
	HINTS "${VORBIS_ROOT}/lib"
)

FIND_LIBRARY(
	VORBIS_FILE_LIBRARY
	NAMES vorbisfile
	HINTS "${VORBIS_ROOT}/lib"
)

FIND_LIBRARY(
	OGG_LIBRARY
	NAMES ogg
	HINTS "${VORBIS_ROOT}/ogg"
)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	VORBIS
	DEFAULT_MSG
	VORBIS_INCLUDE_DIR
	OGG_INCLUDE_DIR
	VORBIS_LIBRARY
	VORBIS_FILE_LIBRARY
	OGG_LIBRARY
)
