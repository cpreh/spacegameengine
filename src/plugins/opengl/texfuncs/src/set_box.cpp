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


#include "../set_box.hpp"
#include "../../check_state.hpp"
#include "../../pbo_context.hpp"
#include "../../vbo_base.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set_box(
	context::object &_context,
	GLenum const _tex_type,
	GLenum const _format,
	GLenum const _type,
	renderer::dim3 const &_dim,
	renderer::lock_box const &_lock_box,
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
			FCPPT_TEXT("ogl::texfuncs::set_box(): src is 0!")
		);

	if(
		_lock_box.right() > _dim.w()
		|| _lock_box.bottom() > _dim.h()
		|| _lock_box.back() > _dim.d()
	)
		throw renderer::exception(
			(
				fcppt::format(
					FCPPT_TEXT("box for setting a texture is out of range (rect=%1%, dim=%2%)!")
				)
				% _lock_box
				% _dim
			)
			.str()
		);

	::glTexSubImage3D(
		_tex_type,
		0,
		static_cast<GLint>(_lock_box.left()),
		static_cast<GLint>(_lock_box.top()),
		static_cast<GLint>(_lock_box.front()),
		static_cast<GLsizei>(_lock_box.w()),
		static_cast<GLsizei>(_lock_box.h()),
		static_cast<GLsizei>(_lock_box.d()),
		_format,
		_type,
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glTexSubImage3D with rect %1% failed")
			)
			% _lock_box
		).str(),
		sge::renderer::exception
	)
}
