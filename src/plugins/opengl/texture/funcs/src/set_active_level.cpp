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


#include "../set_active_level.hpp"
#include "../../multi_context.hpp"
#include "../../convert/level.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include "../../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texture::funcs::set_active_level(
	opengl::context::object &_context,
	renderer::stage const _stage
)
{
	opengl::texture::multi_context &context(
		opengl::context::use<
			opengl::texture::multi_context
		>(
			_context
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
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to set texture stage ")
				<< _stage
				<< FCPPT_TEXT(" but opengl does not support it.")
		);

		return;
	}

	if(
		_stage.get() >=
		static_cast<
			sge::renderer::stage::value_type
		>(
			context.max_level()
		)
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
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
		texture::convert::level(
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
