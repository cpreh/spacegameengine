ADD_EXECUTABLE (sgetest test.cpp)
TARGET_LINK_LIBRARIES (sgetest sgecore)

INSTALL (TARGETS sgetest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (tutorial_01 tutorial/tutorial_01.cpp)
TARGET_LINK_LIBRARIES (tutorial_01 sgecore)

ADD_EXECUTABLE (tutorial_02 tutorial/tutorial_02.cpp)
TARGET_LINK_LIBRARIES (tutorial_02 sgecore)

ADD_EXECUTABLE (font tutorial/font.cpp)
TARGET_LINK_LIBRARIES (font sgecore)

MACRO (ADD_SGE_TEST name)
	ADD_EXECUTABLE (sge${name}test ${name}.cpp)
	TARGET_LINK_LIBRARIES (sge${name}test sgecore)
	INSTALL (TARGETS sge${name}test DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ENDMACRO ()

ADD_SGE_TEST(anim)
ADD_SGE_TEST(doppler)
ADD_SGE_TEST(fullscreen)
ADD_SGE_TEST(pool)
ADD_SGE_TEST(random)
ADD_SGE_TEST(skeleton)
ADD_SGE_TEST(sound)
ADD_SGE_TEST(target)
ADD_SGE_TEST(vertex)

# TODO: this should be part of the macro
#IF (NOT MSVC)
#	TARGET_LINK_LIBRARIES (sgesoundtest ${Boost_program_options_LIBRARIES})
#ENDIF ()

IF (${ENABLE_GUI})
	ADD_SGE_TEST(gui)
	TARGET_LINK_LIBRARIES (sgeguitest sgegui)
ENDIF ()

#ADD_EXECUTABLE (islandtest island/main.cpp quadtree/quadtree.cpp quadtree/mathstuff.cpp island/island_extractor.cpp island/skydome.cpp)
#TARGET_LINK_LIBRARIES (islandtest sgecore)
#INSTALL (TARGETS islandtest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

#ADD_EXECUTABLE (skydometest island/skydome.cpp island/skydome_testcase.cpp)
#TARGET_LINK_LIBRARIES (skydometest sgecore)
#INSTALL (TARGETS skydometest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
