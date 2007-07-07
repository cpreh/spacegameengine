ADD_EXECUTABLE (sgetest test.cpp)
TARGET_LINK_LIBRARIES (sgetest sgecore sgegui boost_signals)

INSTALL (TARGETS sgetest DESTINATION /usr/bin)
