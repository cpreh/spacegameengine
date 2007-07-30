ADD_EXECUTABLE (sgetest test.cpp)
TARGET_LINK_LIBRARIES (sgetest sgecore sgegui boost_signals)
INSTALL (TARGETS sgetest DESTINATION /usr/bin)

ADD_EXECUTABLE (phillemann_test phillemann_main.cpp)
TARGET_LINK_LIBRARIES (phillemann_test sgecore)
INSTALL (TARGETS phillemann_test DESTINATION /usr/bin)
