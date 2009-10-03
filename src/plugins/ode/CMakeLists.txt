FILE (GLOB sgeodefiles src/*.cpp src/shapes/*.cpp)

ADD_LIBRARY (sgeode SHARED ${sgeodefiles})
TARGET_LINK_LIBRARIES (sgeode sgecore ode)

INSTALL (TARGETS sgeode DESTINATION lib/sge)
