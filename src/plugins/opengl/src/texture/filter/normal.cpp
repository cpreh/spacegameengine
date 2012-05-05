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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/context.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/convert/mag_filter.hpp>
#include <sge/opengl/texture/convert/min_filter.hpp>
#include <sge/opengl/texture/filter/normal.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/texture/filter/normal/object.hpp>


void
sge::opengl::texture::filter::normal(
	sge::opengl::context::object &_context,
	sge::opengl::texture::binding const &_binding,
	sge::opengl::texture::type const _type,
	sge::renderer::texture::filter::normal::object const &_filter
)
{
	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		GL_TEXTURE_MAG_FILTER,
		static_cast<
			GLint
		>(
			sge::opengl::texture::convert::mag_filter(
				_filter.mag()
			)
		)
	);

	sge::opengl::texture::funcs::parameter_int(
		_binding,
		_type,
		GL_TEXTURE_MIN_FILTER,
		static_cast<
			GLint
		>(
			sge::opengl::texture::convert::min_filter(
				_filter.min(),
				_filter.mip()
			)
		)
	);

	sge::opengl::texture::context const &texture_context(
		sge::opengl::context::use<
			sge::opengl::texture::context
		>(
			_context
		)
	);

	if(
		texture_context.anisotropic_filter_supported()
	)
		sge::opengl::texture::funcs::parameter_int(
			_binding,
			_type,
			texture_context.anisotropy_flag(),
			1
		);
}
