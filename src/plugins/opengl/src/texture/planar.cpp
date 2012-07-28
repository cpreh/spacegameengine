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


#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/texture/basic_impl.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/opengl/texture/planar_types.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <fcppt/optional_impl.hpp>


template class
sge::opengl::texture::basic<
	sge::opengl::texture::planar_types
>;

sge::opengl::texture::planar::planar(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::planar_parameters const &_parameters,
	sge::opengl::texture::optional_type const &_type
)
:
	sge::opengl::texture::planar_basic(
		_basic_parameters,
		_type
		?
			*_type
		:
			sge::opengl::texture::convert::make_type(
				GL_TEXTURE_2D
			)
		,
		_parameters
	)
{
}

sge::opengl::texture::planar::~planar()
{
}
