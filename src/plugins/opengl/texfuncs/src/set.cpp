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


#include "../set.hpp"
#include "../set_mipmap.hpp"
#include "../../common.hpp"
#include "../../check_state.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/texture_creation_failed.hpp>
#include <fcppt/math/is_power_of_2.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set(
	opengl::context::object &_context,
	GLenum const _texture_type,
	GLenum const _format,
	GLenum const _format_type,
	renderer::filter::texture const &_filter,
	renderer::dim_type const &_dim,
	renderer::const_raw_pointer const _src
)
{
	if(
		_dim.w() < 64 || _dim.h() < 64
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("opengl implementations are not required to support textures smaller than 64x64.")\
				FCPPT_TEXT(" Specified texture size was ")
				<< _dim
				<< FCPPT_TEXT('.')
		);

	if(
		!fcppt::math::is_power_of_2(_dim.w())
		|| !fcppt::math::is_power_of_2(_dim.h())
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("opengl implementations are not required to support textures with dimensions that are not a power of 2.")\
				FCPPT_TEXT(" Specified texture size was ")
				<< _dim
				<< FCPPT_TEXT('.')
		);

	texfuncs::set_mipmap(
		_context,
		_texture_type,
		_filter
	);

	glTexImage2D(
		_texture_type,
		0,
		4,
		static_cast<GLsizei>(_dim.w()),
		static_cast<GLsizei>(_dim.h()),
		0,
		_format,
		_format_type,
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("Creation of texture with size %1% failed!")
			)
			% _dim
		).str(),
		sge::renderer::texture_creation_failed
	);
}
