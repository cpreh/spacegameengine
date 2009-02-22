# - Find VORBIS
# Find the native VORBIS headers and libraries.
#
#  VORBIS_INCLUDE_DIR -  where to find VORBIS.h, etc.
#  VORBIS_LIBRARIES    - List of libraries when using VORBIS.
#  VORBIS_FOUND        - True if VORBIS found.


# Look for the header file.
FIND_PATH(VORBIS_INCLUDE_DIR NAMES vorbis/vorbisfile.h
                             PATHS $ENV{H3D_EXTERNAL_ROOT}/include  
                                   ../../External/include )
MARK_AS_ADVANCED(VORBIS_INCLUDE_DIR)

FIND_PATH(OGG_INCLUDE_DIR NAMES ogg/ogg.h
                          PATHS $ENV{H3D_EXTERNAL_ROOT}/include  
                                ../../External/include )
MARK_AS_ADVANCED(OGG_INCLUDE_DIR)

# Look for the library.
FIND_LIBRARY(VORBIS_LIBRARY NAMES vorbisfile vorbis
                            PATHS $ENV{H3D_EXTERNAL_ROOT}/lib
                                  ../../External/lib)
MARK_AS_ADVANCED(VORBIS_LIBRARY)

FIND_LIBRARY(OGG_LIBRARY NAMES ogg 
                         PATHS $ENV{H3D_EXTERNAL_ROOT}/lib
                               ../../External/lib)
MARK_AS_ADVANCED(OGG_LIBRARY)

# Copy the results to the output variables.
IF(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY)
  SET(VORBIS_FOUND 1)
  SET(VORBIS_LIBRARIES ${VORBIS_LIBRARY} ${OGG_LIBRARY} )
  SET(VORBIS_INCLUDE_DIR ${VORBIS_INCLUDE_DIR} ${OGG_INCLUDE_DIR})
ELSE(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY)
  SET(VORBIS_FOUND 0)
  SET(VORBIS_LIBRARIES)
  SET(VORBIS_INCLUDE_DIR)
ENDIF(VORBIS_INCLUDE_DIR AND VORBIS_LIBRARY)

# Report the results.
IF(NOT VORBIS_FOUND)
  SET(VORBIS_DIR_MESSAGE
    "VORBIS was not found. Make sure VORBIS_LIBRARY and
    VORBIS_INCLUDE_DIR are set to the directories containing the include and lib files for ogg/vorbis. If you do not have the library you will not be able to use ogg files as sound.")
  IF(VORBIS_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "${VORBIS_DIR_MESSAGE}")
  ELSEIF(NOT VORBIS_FIND_QUIETLY)
    MESSAGE(STATUS "${VORBIS_DIR_MESSAGE}")
  ENDIF(VORBIS_FIND_REQUIRED)
ENDIF(NOT VORBIS_FOUND)
