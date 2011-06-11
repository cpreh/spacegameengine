INCLUDE_DIRECTORIES(
	${CEGUI_INCLUDE_DIRS}
)

ADD_SGE_EXAMPLE(text_demo "cegui;systems;time;config" "${CEGUI_LIBRARIES}")
