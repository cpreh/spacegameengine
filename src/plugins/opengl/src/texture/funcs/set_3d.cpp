/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/funcs/set_3d.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/dim3.hpp>
#include <sge/renderer/texture/creation_failed.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/output.hpp>


void
sge::opengl::texture::funcs::set_3d(
	sge::opengl::texture::binding const &,
	sge::opengl::context::object &_context,
	sge::opengl::texture::buffer_type const _buffer_type,
	sge::opengl::color_format const _format,
	sge::opengl::color_format_type const _format_type,
	sge::opengl::internal_color_format const _internal_format,
	sge::renderer::texture::mipmap::level const _level,
	sge::renderer::dim3 const &_dim,
	sge::renderer::const_raw_pointer const _src
)
{
	// TODO: Pass the config into this function
	FCPPT_ASSERT_OPTIONAL_ERROR(
		sge::opengl::context::use<
			sge::opengl::texture::volume_context
		>(
			_context,
			_context.info()
		).config()
	).tex_image_3d()(
		_buffer_type.get(),
		fcppt::cast::to_signed(
			_level.get()
		),
		_internal_format.get(),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_dim.w()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_dim.h()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_dim.d()
			)
		),
		0,
		_format.get(),
		_format_type.get(),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("Creation of texture with size %1% failed!")
			)
			% _dim
		).str(),
		sge::renderer::texture::creation_failed
	);
}
