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


#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/opengl/texture/mipmap/auto_generate.hpp>
#include <sge/opengl/texture/mipmap/generate_levels.hpp>
#include <sge/opengl/texture/mipmap/levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>
#include <fcppt/math/size_type.hpp>


template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::mipmap::levels(
	mipmap::parameters<
		Size
	> const &_parameters,
	renderer::texture::mipmap::levels_rep const &_rep
)
{
	if(
		_rep.auto_generate()
		== renderer::texture::mipmap::auto_generate::yes
	)
	{
		funcs::parameter_int(
			_parameters.binding(),
			_parameters.type(),
			GL_TEXTURE_MAX_LEVEL,
			static_cast<
				GLint
			>(
				_rep.value().get()
			)
		);

		mipmap::auto_generate(
			_parameters.binding(),
			_parameters.context(),
			_parameters.type()
		);
	}
	else
		mipmap::generate_levels(
			_parameters,
			_rep.value()
		);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_LEVELS(\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::levels<\
	dimension\
>(\
	mipmap::parameters<\
		dimension\
	> const &,\
	renderer::texture::mipmap::levels_rep const &\
);

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_LEVELS
)
