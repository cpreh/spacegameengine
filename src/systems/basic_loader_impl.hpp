/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_BASIC_LOADER_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_BASIC_LOADER_IMPL_HPP_INCLUDED

#include <sge/systems/basic_loader.hpp>

template<
	typename Capabilities
>
sge::systems::basic_loader<Capabilities>::basic_loader(
	capabilities_type const &_capabilities,
	sge::extension_set const &_extensions
)
:
	extensions_(_extensions),
	capabilities_(_capabilities)
{}

template<
	typename Capabilities
>
sge::extension_set const &
sge::systems::basic_loader<Capabilities>::extensions() const
{
	return extensions_;
}
	
template<
	typename Capabilities
>
typename sge::systems::basic_loader<Capabilities>::capabilities_type const &
sge::systems::basic_loader<Capabilities>::capabilities() const
{
	return capabilities_;
}

#endif
