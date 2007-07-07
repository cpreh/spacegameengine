FILE (GLOB sgeguifiles src/*.cpp)

ADD_LIBRARY (sgegui SHARED ${sgeguifiles})
TARGET_LINK_LIBRARIES (sgegui sgecore boost_signals)

INSTALL (TARGETS sgegui DESTINATION /usr/lib)
