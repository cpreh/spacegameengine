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


#ifndef SGE_SRC_SYSTEMS_PLUGIN_PAIR_IMPL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_PLUGIN_PAIR_IMPL_HPP_INCLUDED

#include <sge/src/systems/plugin_pair_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename System
>
sge::systems::plugin_pair<
	System
>::plugin_pair(
	plugin &&_plugin,
	system_unique_ptr &&_system
)
:
	plugin_(
		std::move(
			_plugin
		)
	),
	system_(
		std::move(
			_system
		)
	)
{
}

template<
	typename System
>
sge::systems::plugin_pair<
	System
>::plugin_pair(
	plugin_pair &&
) = default;

template<
	typename System
>
sge::systems::plugin_pair<
	System
> &
sge::systems::plugin_pair<
	System
>::operator=(
	plugin_pair &&
) = default;

template<
	typename System
>
sge::systems::plugin_pair<
	System
>::~plugin_pair()
{
}

template<
	typename System
>
System &
sge::systems::plugin_pair<
	System
>::system() const
{
	return
		*system_;
}

#endif
