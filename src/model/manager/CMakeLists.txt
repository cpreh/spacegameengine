set(
	SGE_MODELMANAGER_FILES
	include/sge/model/manager/instance/identifier.hpp
	include/sge/model/manager/instance/object.hpp
	include/sge/model/manager/instance/object_fwd.hpp
	include/sge/model/manager/instance/position.hpp
	include/sge/model/manager/model_directory.hpp
	include/sge/model/manager/object.hpp
	include/sge/model/manager/object_fwd.hpp
	include/sge/model/manager/texture_directory.hpp
	include/sge/model/manager/vf/format.hpp
	include/sge/model/manager/vf/format_part.hpp
	include/sge/model/manager/vf/from_obj_map.hpp
	include/sge/model/manager/vf/normal.hpp
	include/sge/model/manager/vf/position.hpp
	include/sge/model/manager/vf/texcoord.hpp
	src/model/manager/instance/object.cpp
	src/model/manager/object.cpp
)

#include_directories(
#	${CMAKE_CURRENT_SOURCE_DIR}/include
#)

add_sge_base_library(
	"model/manager"
	"sgecore;sgemodelobj;sgerenderer;sgeimage;sgeimage2d;sgecamera"
	"${Fcppt_filesystem_LIBRARIES}"
	""
	""
)
