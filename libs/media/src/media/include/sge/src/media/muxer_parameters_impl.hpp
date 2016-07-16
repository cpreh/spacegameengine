/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/media/muxer_parameters.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <fcppt/log/context_fwd.hpp>


template<
	typename System
>
sge::media::muxer_parameters<
	System
>::muxer_parameters(
	fcppt::log::context &_log_context,
	collection_type const &_collection,
	sge::media::optional_extension_set const &_extensions
)
:
	log_context_(
		_log_context
	),
	collection_(
		_collection
	),
	extensions_(
		_extensions
	)
{
}

template<
	typename System
>
fcppt::log::context &
sge::media::muxer_parameters<
	System
>::log_context() const
{
	return
		log_context_;
}

template<
	typename System
>
typename
sge::media::muxer_parameters<
	System
>::collection_type const &
sge::media::muxer_parameters<
	System
>::collection() const
{
	return
		collection_;
}

template<
	typename System
>
sge::media::optional_extension_set const &
sge::media::muxer_parameters<
	System
>::extensions() const
{
	return
		extensions_;
}

#endif
