SET(
	SGE_MD3_FILES
	src/plugins/md3/funit.hpp
	src/plugins/md3/loader.hpp
	src/plugins/md3/object.hpp
	src/plugins/md3/src/exports.cpp
	src/plugins/md3/src/loader.cpp
	src/plugins/md3/src/object.cpp
	src/plugins/md3/vertex_format.hpp
)

ADD_SGE_PLUGIN(
	md3
	"sgemodel"
)
