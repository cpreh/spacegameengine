FIND_PACKAGE(Bullet)

ADD_SGE_EXAMPLE(projectilemain "input;projectile;renderer;systems;sprite" "${BULLET_LIBRARIES}")
