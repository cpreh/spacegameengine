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


#include "../multi_texture.hpp"
#include "../common.hpp"
#include "../check_state.hpp"
#include "../glew/is_supported.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/format.hpp>
#include <ostream>
#include <algorithm>

namespace
{

bool have_multi_texture()
{
	static bool const ret(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_3"
		)
	);

	return ret;
}

}

void sge::opengl::set_texture_level(
	renderer::stage_type const stage)
{
	if(!have_multi_texture())
	{
		if(stage == 0)
			return;

		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to set texture stage ")
				<< stage
				<< FCPPT_TEXT(" but opengl does not support it.")
		);

		return;
	}

	if(
		stage >= static_cast<renderer::stage_type>(
			std::max(
				GL_MAX_TEXTURE_COORDS,
				GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
			)
		)
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("GL_MAX_COMBINED_TEXTURE_UNITS is ")
				<< GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
				<< FCPPT_TEXT(". Setting texture stage ")
				<< stage
				<< FCPPT_TEXT(" ignored!"));
		return;
	}

	glActiveTexture(
		static_cast<
			GLenum
		>(
			GL_TEXTURE0 + stage
		)
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glActiveTexture failed for stage %1%")
			)
			% stage
		).str(),
		sge::renderer::exception
	)
}

void sge::opengl::client_texture_level(
	renderer::stage_type const stage)
{
	if(!have_multi_texture())
	{
		if(stage == 0)
			return;

		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to set texture coordinates for stage ")
				<< stage
				<< FCPPT_TEXT(" but opengl does not support it.")
		);

		return;
	}

	glClientActiveTexture(
		static_cast<
			GLenum
		>(
			GL_TEXTURE0 + stage
		)
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glClientActiveTexture failed for stage %1%")
			)
			% stage
		).str(),
		sge::renderer::exception
	)
}
