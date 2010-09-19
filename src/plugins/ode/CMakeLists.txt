FILE (GLOB sgeodefiles src/*.cpp src/shapes/*.cpp)

INCLUDE_DIRECTORIES(${ODE_INCLUDE_DIR)}

ADD_LIBRARY (sgeode SHARED ${sgeodefiles})

TARGET_LINK_LIBRARIES (sgeode sgecore ${ODE_LIBRARY})

INSTALL (TARGETS sgeode DESTINATION lib/sge)
