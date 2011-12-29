FIND_PACKAGE(
	Bullet
	REQUIRED
)

add_sge_example(
	projectilemain
	"sgeinput;sgeprojectile;sgerenderer;sgesystems;sgesprite"
	"${BULLET_LIBRARIES}"
)
