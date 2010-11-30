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


#include "../create_caps.hpp"
#include "../common.hpp"
#include "../get_string.hpp"
#include "../get_int.hpp"
#include "../texture_context.hpp"
#include "../fbo_context.hpp"
#include "../glsl/context.hpp"
#include "../context/use.hpp"
#include <sge/renderer/filter/anisotropy_type.hpp>
#include <sge/renderer/adapter_type.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::caps_unique_ptr
sge::opengl::create_caps(
	context::object &_context
)
{
	renderer::size_type const max_texture_size(
		static_cast<
			renderer::size_type
		>(
			opengl::get_int(
				GL_MAX_TEXTURE_SIZE
			)
		)
	);

	return
		fcppt::make_unique_ptr<
			renderer::caps
		>(
			static_cast<
				sge::renderer::adapter_type
			>(
				0 // FIXME!
			),
			get_string(
				GL_VENDOR
			),
			get_string(
				GL_RENDERER
			)
			+ FCPPT_TEXT(' ')
			+ get_string(
				GL_VERSION
			),
			renderer::dim2(
				max_texture_size,
				max_texture_size
			),
			static_cast<
				sge::renderer::filter::anisotropy_type
			>(
				opengl::get_int(
					context::use<
						texture_context
					>(
						_context
					).max_anisotropy_flag()
				)
			),
			context::use<
				fbo_context
			>(
				_context
			).is_supported(),
			context::use<
				glsl::context
			>(
				_context
			).is_supported(),
			sge::image::color::format::rgba8 // TODO: use bgra8 for nvidia instead!
		);
}
