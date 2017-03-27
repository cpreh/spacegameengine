include(
	SGECustomPath
)

set(
	SGE_PLUGIN_INSTALL_PATH
	"${CMAKE_INSTALL_PREFIX}/${PLUGIN_INSTALL_DIR}"
)

set(
	SGE_MEDIA_BUILD_PATH
	"${FCPPT_UTILS_PROJECT_SOURCE_DIR}/media"
)

set(
	SGE_MEDIA_INSTALL_PATH
	"${CMAKE_INSTALL_PREFIX}/${MEDIA_INSTALL_DIR}"
)

sge_config_add_custom_path(
	sge
	media
	${SGE_MEDIA_BUILD_PATH}
	${SGE_MEDIA_INSTALL_PATH}
	MEDIA_INCLUDES
)

sge_config_add_custom_path(
	sge
	plugin
	${SGE_PLUGIN_BUILD_PATH}
	${SGE_PLUGIN_INSTALL_PATH}
	PLUGIN_INCLUDES
)

set(
	SGE_CONFIG_FILES
	libs/config/impl/include/sge/config/impl/try_create_path.hpp
	libs/config/impl/src/config/impl/try_create_path.cpp
	libs/config/include/sge/config/app_name.hpp
	libs/config/include/sge/config/app_path.hpp
	libs/config/include/sge/config/cache_path.hpp
	libs/config/include/sge/config/company_name.hpp
	libs/config/include/sge/config/config_path.hpp
	libs/config/include/sge/config/exception.hpp
	libs/config/include/sge/config/getenv.hpp
	libs/config/include/sge/config/getenv_exn.hpp
	libs/config/include/sge/config/homedir.hpp
	libs/config/include/sge/config/log_path.hpp
	libs/config/include/sge/config/media_path.hpp
	libs/config/include/sge/config/no_such_env_var.hpp
	libs/config/include/sge/config/own_app_name.hpp
	libs/config/include/sge/config/own_company_name.hpp
	libs/config/include/sge/config/own_log_path.hpp
	libs/config/include/sge/config/plugin_path.hpp
	libs/config/include/sge/config/user_name.hpp
	libs/config/src/config/app_path.cpp
	libs/config/src/config/cache_path.cpp
	libs/config/src/config/config_path.cpp
	libs/config/src/config/exception.cpp
	libs/config/src/config/getenv.cpp
	libs/config/src/config/getenv_exn.cpp
	libs/config/src/config/homedir.cpp
	libs/config/src/config/log_path.cpp
	libs/config/src/config/media_path.cpp
	libs/config/src/config/no_such_env_var.cpp
	libs/config/src/config/own_app_name.cpp
	libs/config/src/config/own_company_name.cpp
	libs/config/src/config/own_log_path.cpp
	libs/config/src/config/plugin_path.cpp
	libs/config/src/config/user_name.cpp
)

# TODO: Remove awl dependency here
if(
	WIN32
)
	find_package(
		awl
		REQUIRED
	)

	set(
		SGE_CONFIG_ADDITIONAL_LIBS
		"${awl_TARGET}"
	)
endif()

add_sge_base_library(
	config
	HAS_IMPL_DIR
	SGE_DEPS
		sgecore
	TRANSITIVE_SGE_DEPS
		sgecore
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${fcppt_filesystem_TARGET}
		${SGE_CONFIG_ADDITIONAL_LIBS}
	TRANSITIVE_ADDITIONAL_DEPS
		${Boost_FILESYSTEM_LIBRARIES}
		${Boost_SYSTEM_LIBRARIES}
	INCLUDE_DIRS
		${MEDIA_INCLUDES}
		${PLUGIN_INCLUDES}
)
