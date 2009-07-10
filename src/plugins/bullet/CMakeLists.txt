FILE (GLOB_RECURSE sgebulletfiles src/*.cpp src/objects/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libbullet/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libbullet/lib)
ELSE ()
	pkg_check_modules (BULLET bullet)
	INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIRS})
ENDIF ()

ADD_LIBRARY (sgebullet SHARED ${sgebulletfiles})

TARGET_LINK_LIBRARIES (sgebullet sgecore ${BULLET_LDFLAGS})

INSTALL (TARGETS sgebullet DESTINATION lib/sge)
