//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/impl/library/load_function_base.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/function_map.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/plugin/impl/library/cast_function_unsafe.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/cast/from_void_ptr.hpp>
#endif


sge::plugin::library::function_base
sge::plugin::impl::library::load_function_base(
	sge::plugin::library::object &_object,
	sge::plugin::library::symbol_string const &_name
)
{
	sge::plugin::library::symbol_string const map_name{
		"sge_plugin_functions"
	};

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	using
	map_function
	=
	sge::plugin::library::function_map const *(*)();

	return
		sge::plugin::impl::library::cast_function_unsafe<
			map_function
		>(
			_object.load(
				map_name
			)
		)()->function(
			_name
		);
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	return
		fcppt::cast::from_void_ptr<
			sge::plugin::library::function_map *
		>(
			_object.load(
				map_name
			)
		)->function(
			_name
		);
#else
#error "Don't know how to load library functions!"
#endif
}
