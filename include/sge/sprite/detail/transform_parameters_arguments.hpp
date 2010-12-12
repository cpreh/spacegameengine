/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_TRANSFORM_PARAMETERS_ARGUMENTS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_TRANSFORM_PARAMETERS_ARGUMENTS_HPP_INCLUDED

#include <sge/sprite/detail/transform_init_arguments.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <majutsu/subelements.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename ElementType,
	typename Choices,
	typename Parameters
>
ElementType const
transform_parameters_arguments(
	Parameters const &_parameters
)
{
	ElementType ret(
		detail::transform_init_arguments<
			Choices
		>(
			majutsu::subelements<
				ElementType
			>(
				_parameters
			)
		)
	);

	if(
		_parameters. template get<
			detail::roles::use_center
		>()
	)
		ret. template set<
			sprite::roles::pos
		>(
			ret. template get<
				sprite::roles::pos
			>()
			- ret. template get<
				sprite::roles::size
			>()
			/ static_cast<
				typename Choices::type_choices::unit_type
			>(2u)
		);

	return ret;
}

}
}
}

#endif
