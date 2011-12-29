include(
	SGECustomPath
)

include_directories(
	${CMAKE_BINARY_DIR}/include
)

SGE_CONFIG_ADD_CUSTOM_PATH(
	sge
	media
	${SGE_MEDIA_BUILD_PATH}
	${SGE_MEDIA_INSTALL_PATH}
)

SGE_CONFIG_ADD_CUSTOM_PATH(
	sge
	plugin
	${SGE_PLUGIN_BUILD_PATH}
	${SGE_PLUGIN_INSTALL_PATH}
)

SET(
	SGE_CONFIG_FILES
	include/sge/config/app_path.hpp
	include/sge/config/cache_path.hpp
	include/sge/config/config.hpp
	include/sge/config/config_path.hpp
	include/sge/config/exception.hpp
	include/sge/config/getenv.hpp
	include/sge/config/getenv_exn.hpp
	include/sge/config/homedir.hpp
	include/sge/config/media_path.hpp
	include/sge/config/no_such_env_var.hpp
	include/sge/config/optional_string.hpp
	include/sge/config/plugin_path.hpp
	include/sge/config/symbol.hpp
	src/config/app_path.cpp
	src/config/cache_path.cpp
	src/config/config_path.cpp
	src/config/exception.cpp
	src/config/getenv.cpp
	src/config/getenv_exn.cpp
	src/config/homedir.cpp
	src/config/include/sge/src/config/try_create_path.hpp
	src/config/media_path.cpp
	src/config/no_such_env_var.cpp
	src/config/plugin_path.cpp
	src/config/try_create_path.cpp
)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

ADD_SGE_BASE_LIBRARY(
	config
	"sgecore"
	"${Fcppt_filesystem_LIBRARIES}"
)
