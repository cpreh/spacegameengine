//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/impl/library/version_function_name.hpp>
#include <sge/plugin/library/symbol_string.hpp>


sge::plugin::library::symbol_string
sge::plugin::impl::library::version_function_name()
{
	return
		sge::plugin::library::symbol_string{
			"sge_plugin_version_info"
		};
}
