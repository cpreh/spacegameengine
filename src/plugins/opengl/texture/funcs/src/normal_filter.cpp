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


#include "../normal_filter.hpp"
#include "../parameter_int.hpp"
#include "../../convert/mag_filter.hpp"
#include "../../convert/min_filter.hpp"
#include "../../../common.hpp"
#include <sge/renderer/texture/filter/normal/object.hpp>

void
sge::opengl::texture::funcs::normal_filter(
	texture::scoped_work_bind const &_scoped_work,
	texture::type const _type,
	renderer::texture::filter::normal::object const &_filter
)
{
	funcs::parameter_int(
		_scoped_work,
		_type,
		GL_TEXTURE_MAG_FILTER,
		static_cast<
			GLint
		>(
			texture::convert::mag_filter(
				_filter.mag()
			)
		)
	);

	funcs::parameter_int(
		_scoped_work,
		_type,
		GL_TEXTURE_MIN_FILTER,
		static_cast<
			GLint
		>(
			texture::convert::min_filter(
				_filter.min(),
				_filter.mip()
			)
		)
	);
}
