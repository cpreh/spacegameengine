FILE (GLOB_RECURSE sgelibpngfiles src/*.cpp)

ADD_LIBRARY (sgelibpng SHARED ${sgelibpngfiles})
TARGET_LINK_LIBRARIES (sgelibpng sgecore png)

INSTALL (TARGETS sgelibpng DESTINATION lib/sge)
