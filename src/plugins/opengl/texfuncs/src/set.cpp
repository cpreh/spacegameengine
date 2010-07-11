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


#include "../set.hpp"
#include "../need_mipmap.hpp"
#include "../build_mipmap.hpp"
#include "../../common.hpp"
#include "../../check_state.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture_creation_failed.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <fcppt/math/is_power_of_2.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set(
	GLenum const tex_type,
	GLenum const format,
	GLenum const type,
	renderer::filter::texture const &filter,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer const src
)
{
	if(dim.w() < 64 || dim.h() < 64)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("opengl implementations are not required to support textures smaller than 64x64.")\
				FCPPT_TEXT(" Specified texture size was ")
				<< dim
				<< FCPPT_TEXT('.')
		);

	if(
		!fcppt::math::is_power_of_2(dim.w())
		|| !fcppt::math::is_power_of_2(dim.h())
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("opengl implementations are not required to support textures with dimensions that are not a power of 2.")\
				FCPPT_TEXT(" Specified texture size was ")
				<< dim
				<< FCPPT_TEXT('.')
		);

	glTexImage2D(
		tex_type,
		0,
		4,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		0,
		format,
		type,
		src
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("Creation of texture with size %1% failed!")
			)
			% dim
		).str(),
		sge::renderer::texture_creation_failed
	);

	if(
		texfuncs::need_mipmap(
			filter.min()
		)
	)
		texfuncs::build_mipmap(
			tex_type,
			format,
			type,
			dim,
			src
		);
}
