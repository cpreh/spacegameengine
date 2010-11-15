ADD_SUBDIRECTORY(cg1)
ADD_SUBDIRECTORY(tutorial)

MACRO (ADD_SGE_EXAMPLE EXAMPLE_NAME ADDITONAL_LIBRARIES)
	# Replace slashes
	STRING(REPLACE "/" "" FULL_NAME ${EXAMPLE_NAME})

	SET(FULL_NAME sge${FULL_NAME}example)

	ADD_EXECUTABLE (${FULL_NAME} ${EXAMPLE_NAME}.cpp)

	TARGET_LINK_LIBRARIES (
		${FULL_NAME}
		sgecore
		${ADDITONAL_LIBRARIES}
	)

	INSTALL (TARGETS ${FULL_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ENDMACRO ()

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED
	COMPONENTS
	program_options
)

ADD_SGE_EXAMPLE(anim "")
ADD_SGE_EXAMPLE(appdir "")
ADD_SGE_EXAMPLE(bitmapfont "")
ADD_SGE_EXAMPLE(bloom "")
ADD_SGE_EXAMPLE(caps "")
ADD_SGE_EXAMPLE(cie "")
ADD_SGE_EXAMPLE(collision "")
ADD_SGE_EXAMPLE(configdir "")
#ADD_SGE_EXAMPLE(doppler)
ADD_SGE_EXAMPLE(fullscreen "")
ADD_SGE_EXAMPLE(ini "")
ADD_SGE_EXAMPLE(intrusivesprite "")
ADD_SGE_EXAMPLE(json "")
ADD_SGE_EXAMPLE(mergeimage "")
#ADD_SGE_EXAMPLE(model)
ADD_SGE_EXAMPLE(modifier "")
ADD_SGE_EXAMPLE(plugin "")
#ADD_SGE_EXAMPLE(pool)
ADD_SGE_EXAMPLE(screenshot "")
ADD_SGE_EXAMPLE(shader/main "")
ADD_SGE_EXAMPLE(spritecolor "")
ADD_SGE_EXAMPLE(sound "${Boost_PROGRAM_OPTIONS_LIBRARY}")
ADD_SGE_EXAMPLE(target "")
ADD_SGE_EXAMPLE(vertex "")

#IF(SGE_HAVE_X11)
#	ADD_SGE_EXAMPLE(asio_window)
#ENDIF()

# TODO: this should be part of the macro
#IF (NOT MSVC)
#	TARGET_LINK_LIBRARIES (sgesoundexample ${Boost_program_options_LIBRARIES})
#ENDIF ()

IF (ENABLE_CONSOLE)
	ADD_SGE_EXAMPLE(console "sgeconsole")
ENDIF()

IF (ENABLE_GUI)
	ADD_SGE_EXAMPLE(edit "sgegui")
	ADD_SGE_EXAMPLE(grid "sgegui")
	ADD_SGE_EXAMPLE(gui "sgegui")
ENDIF ()

#ADD_EXECUTABLE (islandexample island/main.cpp quadtree/quadtree.cpp quadtree/mathstuff.cpp island/island_extractor.cpp island/skydome.cpp)
#TARGET_LINK_LIBRARIES (islandexample sgecore)
#INSTALL (TARGETS islandexample DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

#ADD_EXECUTABLE (skydomeexample island/skydome.cpp island/skydome_examplecase.cpp)
#TARGET_LINK_LIBRARIES (skydomeexample sgecore)
#INSTALL (TARGETS skydomeexample DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
