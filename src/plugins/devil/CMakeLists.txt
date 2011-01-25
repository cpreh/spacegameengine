SET(
	SGE_DEVIL_FILES
	src/plugins/devil/error.hpp
	src/plugins/devil/file.hpp
	src/plugins/devil/format.hpp
	src/plugins/devil/image_impl.hpp
	src/plugins/devil/library.hpp
	src/plugins/devil/loader.hpp
	src/plugins/devil/src/error.cpp
	src/plugins/devil/src/exports.cpp
	src/plugins/devil/src/file.cpp
	src/plugins/devil/src/format.cpp
	src/plugins/devil/src/image_impl.cpp
	src/plugins/devil/src/library.cpp
	src/plugins/devil/src/loader.cpp
)

INCLUDE_DIRECTORIES(
	${IL_INCLUDE_DIR}
)

ADD_SGE_PLUGIN(
	"devil"
	"${IL_LIBRARIES};${ILU_LIBRARIES}"
)
