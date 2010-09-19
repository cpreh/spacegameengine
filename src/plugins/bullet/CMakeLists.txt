FILE (GLOB_RECURSE sgebulletfiles src/*.cpp)

INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIRS})

ADD_LIBRARY (sgebullet SHARED ${sgebulletfiles})

TARGET_LINK_LIBRARIES (sgebullet sgecore ${BULLET_LIBRARIES})

INSTALL (TARGETS sgebullet DESTINATION lib/sge)
