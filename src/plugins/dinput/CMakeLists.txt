FILE (GLOB_RECURSE sgedinputfiles src/*.cpp)

INCLUDE_DIRECTORIES(${DINPUT_INCLUDE_DIR})

ADD_LIBRARY (sgedinput SHARED ${sgedinputfiles})

TARGET_LINK_LIBRARIES (sgedinput sgecore ${DINPUT_LIBRARIES})

INSTALL (TARGETS sgedinput DESTINATION lib/sge)
