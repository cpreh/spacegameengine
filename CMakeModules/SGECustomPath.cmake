file(
	WRITE
	${CMAKE_CURRENT_BINARY_DIR}/sge_config_path.hpp.in
"#ifndef SGE_BUILD_CONFIG_PATH_HPP_INCLUDED
#define SGE_BUILD_CONFIG_PATH_HPP_INCLUDED

#cmakedefine SGE_CONFIG_LOCAL_BUILD
#cmakedefine SGE_CONFIG_WINDOWS_LOCAL_PACKAGE

#if defined(SGE_CONFIG_WINDOWS_LOCAL_PACKAGE)
#include <sge/config/app_path.hpp>
#endif

#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#define SGE_CONFIG_TEXT_WRAPPER(\\
	text\\
)\\
	FCPPT_TEXT(\\
		text\\
	)

namespace @SGE_CONFIG_LIBRARY_NAME@
{

inline
boost::filesystem::path const
build_@SGE_CONFIG_PATH_NAME@_path()
{
	return
#if defined(SGE_CONFIG_WINDOWS_LOCAL_PACKAGE)
		sge::config::app_path()
		/
		\"@SGE_CONFIG_LIBRARY_NAME@\"
		/
		\"@SGE_CONFIG_PATH_NAME@\"
#elif defined(SGE_CONFIG_LOCAL_BUILD)
		SGE_CONFIG_TEXT_WRAPPER(
			\"@SGE_CONFIG_BUILD_PATH@\"
		)
#else
		SGE_CONFIG_TEXT_WRAPPER(
			\"@SGE_CONFIG_INSTALL_PATH@\"
		)
#endif
		;
}

}

#undef SGE_CONFIG_TEXT_WRAPPER

#endif
"
)

if(
	WIN32
)
	option(
		SGE_CONFIG_WINDOWS_LOCAL_PACKAGE
		"Build a windows local package"
		OFF
	)
endif()

option(
	SGE_CONFIG_LOCAL_BUILD
	"Create a local build (with local paths for resources)"
	OFF
)

# compatibility for old config
if(
	"${CMAKE_INSTALL_PREFIX}"
	STREQUAL
	""
)
	set(
		SGE_CONFIG_LOCAL_BUILD
		ON
	)
endif()

function(
	SGE_CONFIG_ADD_CUSTOM_PATH
	SGE_CONFIG_LIBRARY_NAME
	SGE_CONFIG_PATH_NAME
	SGE_CONFIG_BUILD_PATH
	SGE_CONFIG_INSTALL_PATH
)
	set(
		SGE_CONFIG_INCLUDE_DIR
		${FCPPT_UTILS_PROJECT_BINARY_DIR}/sgeconfig/include
	)

	configure_file(
		${CMAKE_CURRENT_BINARY_DIR}/sge_config_path.hpp.in
		${SGE_CONFIG_INCLUDE_DIR}/${SGE_CONFIG_LIBRARY_NAME}/build/${SGE_CONFIG_PATH_NAME}_path.hpp
	)

	include_directories(
		${SGE_CONFIG_INCLUDE_DIR}
	)
endfunction()
