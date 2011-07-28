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


#include "../check_dim.hpp"
#include "../instantiate_dim.hpp"
#include "../warn_min.hpp"
#include "../warn_pow2.hpp"

template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::check_dim(
	typename renderer::basic_dim<
		Size
	>::type const &_dim,
	renderer::size_type const _min_value,
	fcppt::string const &_what
)
{
	opengl::texture::warn_min(
		_dim,
		_min_value,
		_what
	);

	opengl::texture::warn_pow2(
		_dim,
		_what
	);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM(\
	dimension\
)\
template \
void \
sge::opengl::texture::check_dim<\
	dimension\
>(\
	sge::renderer::basic_dim< \
		dimension \
	>::type const &, \
	sge::renderer::size_type, \
	fcppt::string const & \
);

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM
)
