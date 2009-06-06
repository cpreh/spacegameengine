FILE (GLOB_RECURSE sgebitmapfontfiles src/*.cpp)

ADD_LIBRARY (sgebitmapfont SHARED ${sgebitmapfontfiles})

TARGET_LINK_LIBRARIES (sgebitmapfont sgecore)

INSTALL (TARGETS sgebitmapfont DESTINATION ${pluginpath})
