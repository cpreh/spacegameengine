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


#include "../set_mipmap.hpp"
#include "../parameter_int.hpp"
#include "../need_mipmap.hpp"
#include "../../texture_context.hpp"
#include "../../common.hpp"
#include "../../context/use.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set_mipmap(
	opengl::context::object &_context,
	GLenum const _texture_type,
	renderer::filter::texture const &_filter
)
{
	bool const need_mipmap(
		texfuncs::need_mipmap(
			_filter.min()
		)
	);

	if(
		!opengl::context::use<
			texture_context
		>(
			_context
		).generate_mipmap_flag_supported()
	)
	{
		if(
			need_mipmap
		)
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Building mipmaps is not supported.")
					<< FCPPT_TEXT(" The min_filter will not work correctly.")
			);

		return;
	}
	
	texfuncs::parameter_int(
		_texture_type,
		GL_GENERATE_MIPMAP,
		need_mipmap
	);
}
