SET(
	SGE_LIBPNG_FILES
	src/plugins/libpng/byte_vector.hpp
	src/plugins/libpng/context_base.hpp
	src/plugins/libpng/file.hpp
	src/plugins/libpng/load_context.hpp
	src/plugins/libpng/loader.hpp
	src/plugins/libpng/logger.hpp
	src/plugins/libpng/read_ptr.hpp
	src/plugins/libpng/src/context_base.cpp
	src/plugins/libpng/src/exports.cpp
	src/plugins/libpng/src/file.cpp
	src/plugins/libpng/src/load_context.cpp
	src/plugins/libpng/src/loader.cpp
	src/plugins/libpng/src/logger.cpp
	src/plugins/libpng/src/read_ptr.cpp
	src/plugins/libpng/src/write_context.cpp
	src/plugins/libpng/src/write_ptr.cpp
	src/plugins/libpng/write_context.hpp
	src/plugins/libpng/write_ptr.hpp
)

INCLUDE_DIRECTORIES(
	${PNG_INCLUDE_DIR}
)

ADD_DEFINITIONS(
	${PNG_DEFINITIONS}
)

ADD_SGE_PLUGIN(
	libpng
	"${PNG_LIBRARY}"
)
