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


#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/mipmap/all_levels.hpp>
#include <sge/opengl/texture/mipmap/levels.hpp>
#include <sge/opengl/texture/mipmap/visitor.hpp>


template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::mipmap::visitor<Dim>::visitor(
	parameters const &_parameters
)
:
	parameters_(_parameters)
{
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::visitor<Dim>::result_type
sge::opengl::texture::mipmap::visitor<Dim>::operator()(
	renderer::texture::mipmap::off_rep const &
) const
{
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::visitor<Dim>::result_type
sge::opengl::texture::mipmap::visitor<Dim>::operator()(
	renderer::texture::mipmap::all_levels_rep const &_all_levels
) const
{
	mipmap::all_levels(
		parameters_,
		_all_levels
	);
}

template<
	fcppt::math::size_type Dim
>
typename sge::opengl::texture::mipmap::visitor<Dim>::result_type
sge::opengl::texture::mipmap::visitor<Dim>::operator()(
	renderer::texture::mipmap::levels_rep const &_levels
) const
{
	mipmap::levels(
		parameters_,
		_levels
	);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_VISITOR(\
	dimension\
)\
template class \
sge::opengl::texture::mipmap::visitor<\
	dimension\
>;

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_VISITOR
)
