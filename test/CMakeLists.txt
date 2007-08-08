ADD_EXECUTABLE (sgetest test.cpp)
TARGET_LINK_LIBRARIES (sgetest sgecore boost_signals)
INSTALL (TARGETS sgetest DESTINATION /usr/bin)

#ADD_SUBDIRECTORY (quadtree)

ADD_EXECUTABLE (soundtest soundtest.cpp)
TARGET_LINK_LIBRARIES (soundtest sgecore)
INSTALL (TARGETS soundtest DESTINATION /usr/bin)
