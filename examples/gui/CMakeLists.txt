find_package(
	CEGUI
	REQUIRED
)

include_directories(
	"${CEGUI_INCLUDE_DIRS}"
)

add_sge_example(
	text_demo
	"sgecegui;sgeconfig;sgeimage;sgeinput;sgelog;sgerenderer;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES}"
)
