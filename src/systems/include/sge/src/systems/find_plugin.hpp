/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_FIND_PLUGIN_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_FIND_PLUGIN_HPP_INCLUDED

#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/object_shared_ptr.hpp>
#include <sge/src/systems/plugin_pair_decl.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <typeinfo>
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
> const
find_plugin(
	sge::plugin::collection<
		System
	> const &_collection,
	sge::systems::optional_name const &_name,
	TestFunction const &_test_function
)
{
	typedef sge::plugin::iterator<
		System
	> iterator;

	typedef sge::systems::plugin_pair<
		System
	> return_type;

	for(
		iterator it(
			_collection.begin()
		);
		it != _collection.end();
		++it
	)
	{
		bool const name_is_same(
			_name
			&&
			*_name
			==
			it->info().name()
		);

		if(
			_name
			&&
			!name_is_same
		)
			continue;

		typedef typename sge::plugin::object_shared_ptr<
			System
		>::type plugin_shared_ptr;

		plugin_shared_ptr const plugin(
			it->load()
		);

		typedef std::unique_ptr<
			System
		> system_unique_ptr;

		typedef fcppt::shared_ptr<
			System
		> system_shared_ptr;

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
					plugin,
					system_shared_ptr(
						std::move(
							system
						)
					)
				);
		else if(
			name_is_same
		)
			throw sge::systems::exception(
				FCPPT_TEXT("Plugin of type ")
				+
				fcppt::type_name(
					typeid(
						System
					)
				)
				+
				FCPPT_TEXT(" and name ")
				+
				_name->get()
				+
				FCPPT_TEXT(" was explicitly requested but doesn't match the requested capabilities.")
			);
	}

	throw sge::systems::exception(
		FCPPT_TEXT("No plugin of type ")
		+
		fcppt::type_name(
			typeid(
				System
			)
		)
		+
		(
			_name
			?
				FCPPT_TEXT(" and with name ")
				+
				_name->get()
				+
				FCPPT_TEXT(" found.")
			:
				FCPPT_TEXT(" matched the requested capabilities.")
		)
	);
}

}
}

#endif
