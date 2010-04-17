FILE (
	GLOB_RECURSE sgexcbfiles
	*.cpp
	visual/*.cpp
	window/*.cpp
)

ADD_LIBRARY (sgexcb SHARED ${sgexcbfiles})

TARGET_LINK_LIBRARIES (sgexcb sgecore)

INSTALL (TARGETS sgexcb DESTINATION lib)

INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/sge/xcb DESTINATION include/sge)
