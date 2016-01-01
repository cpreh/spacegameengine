/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/opengl/texture/mipmap/auto_generate.hpp>
#include <sge/opengl/texture/mipmap/context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::texture::mipmap::auto_generate(
	sge::opengl::texture::binding const &_binding,
	sge::opengl::context::object &_context
)
{
	fcppt::optional::maybe(
		sge::opengl::context::use<
			sge::opengl::texture::mipmap::context
		>(
			_context,
			_context.info()
		).generate_mipmap_flag(),
		[]{
			FCPPT_LOG_ERROR(
				sge::opengl::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("Building mipmaps is not supported.")
					<< FCPPT_TEXT(" The mip_filter will not work correctly.")
			);
		},
		[
			&_binding
		](
			GLenum const _generate_mipmap_flag
		)
		{
			sge::opengl::texture::funcs::parameter_int(
				_binding,
				_generate_mipmap_flag,
				GL_TRUE
			);
		}
	);
}
