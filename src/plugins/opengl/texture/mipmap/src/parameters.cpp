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


#include "../parameters.hpp"
#include "../../instantiate_dim.hpp"

template<
	fcppt::math::size_type Dim
>
sge::opengl::texture::mipmap::parameters<Dim>::parameters(
	texture::scoped_work_bind const &_scoped_work,
	opengl::context::object &_context,
	texture::type const _type,
	dim const &_size,
	init_function_type const &_init_function
)
:
	scoped_work_(_scoped_work),
	context_(_context),
	type_(_type),
	size_(_size),
	init_function_(_init_function)
{
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS(\
	dimension\
)\
template class \
sge::opengl::texture::mipmap::parameters<\
	dimension\
>;

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_PARAMETERS
)
