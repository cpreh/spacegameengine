/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../set_rect.hpp"
#include "../need_mipmap.hpp"
#include "../../check_state.hpp"
#include "../../pbo_context.hpp"
#include "../../vbo_base.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/filter/texture.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set_rect(
	context::object &_context,
	GLenum const _tex_type,
	GLenum const _format,
	GLenum const _type,
	renderer::filter::texture const &_filter,
	renderer::dim_type const &_dim,
	renderer::lock_rect const &_lock_rect,
	renderer::const_raw_pointer const _src
)
{
	if(!
		_src && 
		!context::use<
			pbo_context
		>(
			_context
		)
		.impl()
		.hardware_supported()
	)
		throw renderer::exception(
			FCPPT_TEXT("ogl::set_texture_rect(): src is 0!")
		);

	if(
		_lock_rect.right() > _dim.w()
		|| _lock_rect.bottom() > _dim.h()
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("rect for setting a texture is out of range (rect=%1%, dim=%2%)!")
				)
				% _lock_rect
				% _dim
			)
			.str()
		);

	if(
		texfuncs::need_mipmap(
			_filter.min()
		)
	)
		throw renderer::exception(
			FCPPT_TEXT("You can't specify an update rect while using mipmaps.")
		);

	::glTexSubImage2D(
		_tex_type,
		0,
		static_cast<GLint>(_lock_rect.left()),
		static_cast<GLint>(_lock_rect.top()),
		static_cast<GLsizei>(_lock_rect.w()),
		static_cast<GLsizei>(_lock_rect.h()),
		_format,
		_type,
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glTexSubImage2D with rect %1% failed")
			)
			% _lock_rect
		).str(),
		sge::renderer::exception
	)
}
