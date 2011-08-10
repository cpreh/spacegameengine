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


#include "../set_client_level.hpp"
#include "../../multi_context.hpp"
#include "../../convert/level.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include "../../../context/use.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texture::funcs::set_client_level(
	context::object &_context,
	renderer::stage const _stage
)
{
	texture::multi_context &context(
		opengl::context::use<
			texture::multi_context
		>(
			_context
		)
	);

	if(
		!context.is_supported()
	)
	{
		if(
			_stage.get() == 0u
		)
			return;

		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Tried to set texture coordinates for stage ")
				<< _stage
				<< FCPPT_TEXT(" but opengl does not support it.")
		);

		return;
	}

	context.client_active_texture()(
		texture::convert::level(
			_stage
		)
	);

	SGE_OPENGL_CHECK_STATE(
		(
			fcppt::format(
				FCPPT_TEXT("glClientActiveTexture failed for stage %1%")
			)
			% _stage
		).str(),
		sge::renderer::exception
	)
}
