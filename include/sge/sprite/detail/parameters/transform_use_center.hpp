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


#ifndef SGE_SPRITE_DETAIL_PARAMETERS_TRANSFORM_USE_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PARAMETERS_TRANSFORM_USE_CENTER_HPP_INCLUDED

#include <sge/sprite/detail/config/needs_use_center.hpp>
#include <sge/sprite/detail/parameters/transform_use_texture_size.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace parameters
{

template<
	typename Choices,
	typename Parameters
>
typename boost::enable_if<
	sge::sprite::detail::config::needs_use_center<
		Choices
	>,
	Parameters
>::type const
transform_use_center(
	Parameters const &_parameters
)
{
	Parameters ret(
		sge::sprite::detail::parameters::transform_use_texture_size<
			Choices
		>(
			_parameters
		)
	);

	if(
		_parameters. template get<
			sge::sprite::detail::roles::use_center
		>()
	)
		ret. template set<
			sge::sprite::roles::pos
		>(
			ret. template get<
				sge::sprite::roles::pos
			>()
			-
			ret. template get<
				sge::sprite::roles::size
			>()
			/
			static_cast<
				typename Choices::type_choices::unit_type
			>(
				2u
			)
		);

	return ret;
}

template<
	typename Choices,
	typename Parameters
>
typename boost::disable_if<
	sge::sprite::detail::config::needs_use_center<
		Choices
	>,
	Parameters
>::type const
transform_use_center(
	Parameters const &_parameters
)
{
	return
		sge::sprite::detail::parameters::transform_use_texture_size<
			Choices
		>(
			_parameters
		);
}

}
}
}
}

#endif
