FILE (GLOB sgeguifiles *.cpp events/*.cpp layouts/*.cpp widgets/*.cpp)

ADD_LIBRARY (sgegui SHARED ${sgeguifiles})
TARGET_LINK_LIBRARIES (sgegui sgecore)

INSTALL (TARGETS sgegui DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

INSTALL_HEADERS (${CMAKE_SOURCE_DIR}/sge/gui)
