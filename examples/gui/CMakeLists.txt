find_package(
	CEGUI
	REQUIRED
)

include_directories(
	"${CEGUI_INCLUDE_DIRS}"
)

add_sge_example(
	text_demo
	"sgecegui;sgesystems;sgeconfig"
	"${CEGUI_LIBRARIES}"
)
