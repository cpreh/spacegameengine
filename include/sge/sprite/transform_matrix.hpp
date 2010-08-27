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


#ifndef SGE_SPRITE_TRANSFORM_MATRIX_HPP_INCLUDED
#define SGE_SPRITE_TRANSFORM_MATRIX_HPP_INCLUDED

#include <sge/sprite/matrix.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
typename sprite::matrix<
	typename Choices::float_type
>::type const
transform_matrix(
	sge::renderer::dim_type const &_dim
)
{
	return
		renderer::matrix_pixel_to_space<
			typename Choices::type_choices::float_type
		>(
			_dim
		);
}

}
}

#endif
