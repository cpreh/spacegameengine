//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/build/plugin_path.hpp>
#include <sge/config/plugin_path.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


std::filesystem::path
sge::config::plugin_path()
{
	return
		sge::build_plugin_path()
#if defined(SGE_CONFIG_LOCAL_BUILD) && defined(CMAKE_INTDIR)
		/
		fcppt::from_std_string(
			CMAKE_INTDIR
		)
#endif
		;
}
