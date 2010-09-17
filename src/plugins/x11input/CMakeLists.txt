FILE (GLOB_RECURSE sgex11inputfiles src/*.cpp)

ADD_LIBRARY (sgex11input SHARED ${sgex11inputfiles})
TARGET_LINK_LIBRARIES (sgex11input sgecore ${X11_LIBRARIES})

INSTALL (TARGETS sgex11input DESTINATION lib/sge)
