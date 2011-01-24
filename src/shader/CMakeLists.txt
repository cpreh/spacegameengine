SET(
	SGE_SHADER_FILES
	include/sge/shader/format_printer.hpp
	include/sge/shader/mat4.hpp
	include/sge/shader/object.hpp
	include/sge/shader/object_fwd.hpp
	include/sge/shader/object_ptr.hpp
	include/sge/shader/sampler.hpp
	include/sge/shader/sampler_sequence.hpp
	include/sge/shader/scalar.hpp
	include/sge/shader/scoped.hpp
	include/sge/shader/symbol.hpp
	include/sge/shader/texture_variant.hpp
	include/sge/shader/texture_variant_impl.hpp
	include/sge/shader/value_type.hpp
	include/sge/shader/variable.hpp
	include/sge/shader/variable_sequence.hpp
	include/sge/shader/variable_type.hpp
	include/sge/shader/vec2.hpp
	include/sge/shader/vec3.hpp
	include/sge/shader/vec4.hpp
	include/sge/shader/vector_to_string.hpp
	include/sge/shader/vf_to_string.hpp
	src/shader/object.cpp
	src/shader/sampler.cpp
	src/shader/scoped.cpp
	src/shader/variable.cpp
)

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_SHADER_FILES}"
	SGE_SHADER_FILES_ABS
)

ADD_LIBRARY(
	sgeshader
	SHARED
	${SGE_SHADER_FILES_ABS}
)

TARGET_LINK_LIBRARIES(
	sgeshader
	sgecore
)

INSTALL(
	TARGETS
	sgeshader
	DESTINATION
	lib
)

INSTALL(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/sge/shader
	DESTINATION
	include/sge
)
