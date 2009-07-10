FILE (GLOB_RECURSE sgeguifiles
	*.cpp)

ADD_LIBRARY (sgegui SHARED ${sgeguifiles})
TARGET_LINK_LIBRARIES (sgegui sgecore)

INSTALL (TARGETS sgegui DESTINATION lib)

INSTALL(DIRECTORY include/sge/gui DESTINATION include/sge/gui)
