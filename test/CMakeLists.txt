ADD_EXECUTABLE (sgetest test.cpp)
TARGET_LINK_LIBRARIES (sgetest sgecore)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (sgetest boost_signals)
ENDIF ()

INSTALL (TARGETS sgetest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (soundtest soundtest.cpp)
TARGET_LINK_LIBRARIES (soundtest sgecore)
INSTALL (TARGETS soundtest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (animtest animtest.cpp)
TARGET_LINK_LIBRARIES (animtest sgecore)
INSTALL (TARGETS animtest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (tutorial_01 tutorial/tutorial_01.cpp)
TARGET_LINK_LIBRARIES (tutorial_01 sgecore)

ADD_EXECUTABLE (tutorial_02 tutorial/tutorial_02.cpp)
TARGET_LINK_LIBRARIES (tutorial_02 sgecore)

ADD_EXECUTABLE (font tutorial/font.cpp)
TARGET_LINK_LIBRARIES (font sgecore)

ADD_EXECUTABLE (giltest giltest.cpp)
TARGET_LINK_LIBRARIES (giltest sgecore)
INSTALL (TARGETS giltest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (targettest targettest.cpp)
TARGET_LINK_LIBRARIES (targettest sgecore)
INSTALL (TARGETS targettest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

IF (${ENABLE_GUI})
	ADD_EXECUTABLE (sgeguitest guitest.cpp)
	TARGET_LINK_LIBRARIES (sgeguitest sgecore sgegui boost_signals)
	INSTALL (TARGETS sgeguitest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
ENDIF ()

#ADD_EXECUTABLE (islandtest island/main.cpp quadtree/quadtree.cpp quadtree/mathstuff.cpp island/island_extractor.cpp island/skydome.cpp)
#TARGET_LINK_LIBRARIES (islandtest sgecore)
#INSTALL (TARGETS islandtest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

#ADD_EXECUTABLE (skydometest island/skydome.cpp island/skydome_testcase.cpp)
#TARGET_LINK_LIBRARIES (skydometest sgecore)
#INSTALL (TARGETS skydometest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
