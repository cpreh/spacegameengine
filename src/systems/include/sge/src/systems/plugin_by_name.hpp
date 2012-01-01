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


#ifndef SGE_SRC_SYSTEMS_PLUGIN_BY_NAME_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_PLUGIN_BY_NAME_HPP_INCLUDED

#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/object_shared_ptr.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename T
>
typename sge::plugin::object_shared_ptr<
	T
>::type const
plugin_by_name(
	sge::plugin::manager &_manager,
	sge::systems::optional_name const &_name
)
{
	if(
		!_name
	)
		return
			_manager.plugin<
				T
			>().load();

	for(
		plugin::iterator<T> it(
			_manager.begin<T>()
		);
		it != _manager.end<T>();
		++it
	)
		if(
			it->base().info().name()
			== *_name
		)
			return it->load();

	throw sge::systems::exception(
		FCPPT_TEXT("Plugin of type \"")
		+ fcppt::type_name(
			typeid(
				T
			)
		)
		+ FCPPT_TEXT("\" with name \"")
		+ *_name
		+ FCPPT_TEXT("\" not found!")
	);
}

}
}

#endif
