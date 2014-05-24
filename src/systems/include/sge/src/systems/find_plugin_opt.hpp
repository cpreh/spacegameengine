/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/object_unique_ptr.hpp>
#include <sge/src/systems/plugin_pair_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
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
sge::systems::plugin_pair<
	System
>
find_plugin_opt(
	sge::plugin::collection<
		System
	> const &_collection,
	TestFunction const &_test_function
)
{
	typedef sge::systems::plugin_pair<
		System
	> return_type;

	for(
		auto element
		:
		_collection
	)
	{
		typedef
		sge::plugin::object_unique_ptr<
			System
		>
		plugin_unique_ptr;

		plugin_unique_ptr plugin(
			element.load()
		);

		typedef std::unique_ptr<
			System
		> system_unique_ptr;

		system_unique_ptr system(
			plugin->get()()
		);

		if(
			_test_function(
				*system
			)
		)
			return
				return_type(
					std::move(
						plugin
					),
					std::move(
						system
					)
				);
	}

	return
		return_type();
}

}
}

#endif
