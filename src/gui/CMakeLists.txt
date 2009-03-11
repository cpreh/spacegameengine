FILE (GLOB sgeguifiles 
		*.cpp 
		events/*.cpp 
		layouts/*.cpp 
		widgets/*.cpp 
		widgets/buttons/*.cpp 
		skins/*.cpp 
		timer/*.cpp 
		canvas/*.cpp 
		skins/standard/*.cpp 
		skins/standard/buttons/*.cpp 
		utility/*.cpp
		detail/*.cpp 
		detail/managers/*.cpp)

ADD_LIBRARY (sgegui SHARED ${sgeguifiles})
TARGET_LINK_LIBRARIES (sgegui sgecore)

INSTALL (TARGETS sgegui DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

INSTALL_HEADERS (${CMAKE_SOURCE_DIR}/sge/gui)
