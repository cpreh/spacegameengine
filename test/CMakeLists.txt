ADD_EXECUTABLE (sgetest test.cpp)
#TARGET_LINK_LIBRARIES (sgetest sgecore boost_signals boost_iostreams)
TARGET_LINK_LIBRARIES (sgetest sgecore boost_signals)
INSTALL (TARGETS sgetest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

ADD_EXECUTABLE (soundtest soundtest.cpp)
TARGET_LINK_LIBRARIES (soundtest sgecore)
INSTALL (TARGETS soundtest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

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
