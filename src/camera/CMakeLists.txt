SET(
	SGE_CAMERA_FILES
	include/sge/camera/gizmo/basic.hpp
	include/sge/camera/gizmo/to_rotation_matrix.hpp
	include/sge/camera/gizmo_type.hpp
	include/sge/camera/identity_gizmo.hpp
	include/sge/camera/object.hpp
	include/sge/camera/parameters.hpp
	include/sge/camera/parameters_fwd.hpp
	include/sge/camera/projection/object.hpp
	include/sge/camera/projection/orthogonal.hpp
	include/sge/camera/projection/perspective.hpp
	include/sge/camera/projection/to_matrix.hpp
	include/sge/camera/symbol.hpp
	src/camera/identity_gizmo.cpp
	src/camera/object.cpp
	src/camera/parameters.cpp
	src/camera/projection/perspective.cpp
	src/camera/projection/to_matrix.cpp
)

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_CAMERA_FILES}"
	SGE_CAMERA_FILES_ABS
)

ADD_LIBRARY(
	sgecamera
	SHARED
	${SGE_CAMERA_FILES_ABS}
)

TARGET_LINK_LIBRARIES(
	sgecamera
	sgecore
)

INSTALL(
	TARGETS
	sgecamera
	DESTINATION
	lib
)

INSTALL(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/sge/camera
	DESTINATION
	include/sge
)
