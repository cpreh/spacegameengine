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


#include <sge/opengl/texture/funcs/set_3d.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/texture/creation_failed.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>


void
sge::opengl::texture::funcs::set_3d(
	texture::scoped_work_bind const &,
	opengl::context::object &_context,
	texture::type const _type,
	opengl::color_format const _format,
	opengl::color_format_type const _format_type,
	opengl::internal_color_format const _internal_format,
	renderer::stage const _stage,
	renderer::dim3 const &_dim,
	renderer::const_raw_pointer const _src
)
{
	context::use<
		opengl::texture::volume_context
	>(
		_context
	).tex_image_3d()(
		_type.get(),
		static_cast<
			GLint
		>(
			_stage.get()
		),
		_internal_format.get(),
		static_cast<
			GLsizei
		>(
			_dim.w()
		),
		static_cast<
			GLsizei
		>(
			_dim.h()
		),
		static_cast<
			GLsizei
		>(
			_dim.d()
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
