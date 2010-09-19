FILE (GLOB_RECURSE sgefreetypefiles src/*.cpp)

INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})

ADD_LIBRARY (sgefreetype SHARED ${sgefreetypefiles})

TARGET_LINK_LIBRARIES (sgefreetype sgecore ${FREETYPE_LIBRARIES})

INSTALL (TARGETS sgefreetype DESTINATION lib/sge)
