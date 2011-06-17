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
	include/sge/config/appdir.hpp
	include/sge/config/config.hpp
	include/sge/config/exception.hpp
	include/sge/config/find_cache_path.hpp
	include/sge/config/find_config_path.hpp
	include/sge/config/getenv.hpp
	include/sge/config/getenv_exn.hpp
	include/sge/config/homedir.hpp
	include/sge/config/media_path.hpp
	include/sge/config/no_such_env_var.hpp
	include/sge/config/optional_string.hpp
	include/sge/config/plugin_path.hpp
	include/sge/config/symbol.hpp
	src/config/appdir.cpp
	src/config/exception.cpp
	src/config/find_cache_path.cpp
	src/config/find_config_path.cpp
	src/config/getenv.cpp
	src/config/getenv_exn.cpp
	src/config/homedir.cpp
	src/config/media_path.cpp
	src/config/no_such_env_var.cpp
	src/config/plugin_path.cpp
	src/config/try_create_path.cpp
	src/config/try_create_path.hpp
)

ADD_SGE_BASE_LIBRARY(
	config
	""
)
