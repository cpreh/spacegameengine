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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/logger.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/convert/level.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/format.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/warning.hpp>


void
sge::opengl::texture::funcs::set_active_level(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::multi_context &context(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_system_context
		)
	);

	if(
		!context.is_supported()
	)
	{
		if(
			_stage.get() == 0
		)
			return;

		FCPPT_LOG_ERROR(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to set texture stage ")
				<< _stage
				<< FCPPT_TEXT(" but opengl does not support it.")
		);

		return;
	}

	if(
		_stage.get()
		>=
		context.max_level().get()
	)
	{
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("GL_MAX_COMBINED_TEXTURE_UNITS is ")
				<< context.max_level()
				<< FCPPT_TEXT(". Setting texture stage ")
				<< _stage
				<< FCPPT_TEXT(" ignored!")
		);

		return;
	}

	context.active_texture()(
		sge::opengl::texture::convert::level(
			_stage
		)
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glActiveTexture failed for stage %1%")
			)
			% _stage
		).str(),
		sge::renderer::exception
	)
}
