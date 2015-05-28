/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SRC_SYSTEMS_FIND_PLUGIN_OPT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_FIND_PLUGIN_OPT_HPP_INCLUDED

#include <sge/log/option_container.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/load_with_log_options.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/systems/plugin_pair_decl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename System,
	typename TestFunction
>
fcppt::optional<
	sge::systems::plugin_pair<
		System
	>
>
find_plugin_opt(
	sge::plugin::collection<
		System
	> const &_collection,
	sge::log::option_container const &_log_options,
	TestFunction const &_test_function
)
{
	typedef
	sge::systems::plugin_pair<
		System
	>
	pair_type;

	typedef
	fcppt::optional<
		pair_type
	>
	return_type;

	for(
		auto const &element
		:
		_collection
	)
	{
		typedef
		sge::plugin::object<
			System
		>
		plugin_type;

		plugin_type plugin(
			sge::plugin::load_with_log_options(
				element,
				_log_options
			)
		);

		typedef
		fcppt::unique_ptr<
			System
		>
		system_unique_ptr;

		system_unique_ptr system(
			plugin.get()()
		);

		if(
			_test_function(
				*system
			)
		)
			return
				return_type(
					pair_type(
						std::move(
							plugin
						),
						std::move(
							system
						)
					)
				);
	}

	return
		return_type();
}

}
}

#endif
