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


#ifndef SGE_SRC_MEDIA_MUXER_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SRC_MEDIA_MUXER_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/media/extension_set.hpp>
#include <sge/media/muxer_parameters.hpp>
#include <sge/plugin/manager_fwd.hpp>


template<
	typename Capabilities
>
sge::media::muxer_parameters<
	Capabilities
>::muxer_parameters(
	plugin::manager &_manager,
	media::extension_set const &_extensions,
	capabilities_type const &_capabilities
)
:
	manager_(
		_manager
	),
	extensions_(
		_extensions
	),
	capabilities_(
		_capabilities
	)
{
}

template<
	typename Capabilities
>
sge::plugin::manager &
sge::media::muxer_parameters<
	Capabilities
>::manager() const
{
	return manager_;
}

template<
	typename Capabilities
>
sge::media::extension_set const &
sge::media::muxer_parameters<
	Capabilities
>::extensions() const
{
	return extensions_;
}

template<
	typename Capabilities
>
typename sge::media::muxer_parameters<
	Capabilities
>::capabilities_type const &
sge::media::muxer_parameters<
	Capabilities
>::capabilities() const
{
	return capabilities_;
}

#endif
