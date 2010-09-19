FILE (GLOB_RECURSE sgeopenalfiles src/*.cpp)

INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIR})

ADD_LIBRARY (sgeopenal SHARED ${sgeopenalfiles})

TARGET_LINK_LIBRARIES (sgeopenal sgecore ${OPENAL_LIBRARY})

INSTALL (TARGETS sgeopenal DESTINATION lib/sge)
