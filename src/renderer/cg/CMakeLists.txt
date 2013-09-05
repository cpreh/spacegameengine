remove_definitions(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)

set(
	SGE_RENDERERCG_FILES
	include/sge/renderer/cg/loaded_program.hpp
	include/sge/renderer/cg/loaded_program_fwd.hpp
	include/sge/renderer/cg/loaded_program_scoped_ptr.hpp
	include/sge/renderer/cg/loaded_program_unique_ptr.hpp
	include/sge/renderer/cg/loaded_texture.hpp
	include/sge/renderer/cg/loaded_texture_fwd.hpp
	include/sge/renderer/cg/loaded_texture_scoped_ptr.hpp
	include/sge/renderer/cg/loaded_texture_unique_ptr.hpp
	include/sge/renderer/cg/scoped_program.hpp
	include/sge/renderer/cg/scoped_program_fwd.hpp
	include/sge/renderer/cg/scoped_texture.hpp
	include/sge/renderer/cg/scoped_texture_fwd.hpp
	src/renderer/cg/loaded_program.cpp
	src/renderer/cg/loaded_texture.cpp
	src/renderer/cg/scoped_program.cpp
	src/renderer/cg/scoped_texture.cpp
)

add_sge_base_library(
	"renderer/cg"
	""
	""
	""
	""
	""
	""
	"sgecg"
)
