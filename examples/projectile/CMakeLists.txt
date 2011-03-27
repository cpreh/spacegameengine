FIND_PACKAGE(Bullet)

INCLUDE_DIRECTORIES(
	${BULLET_INCLUDE_DIRS})

ADD_SGE_EXAMPLE(projectilemain "projectile;systems;sprite;time" "${BULLET_LIBRARIES}")
