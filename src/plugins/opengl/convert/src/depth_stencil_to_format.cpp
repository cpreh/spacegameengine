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


#include "../depth_stencil_to_format.hpp"
#include "../../common.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::color_format const
sge::opengl::convert::depth_stencil_to_format(
	renderer::depth_stencil_format::type const _format
)
{
	switch(
		_format
	)
	{
	case renderer::depth_stencil_format::d16:
	case renderer::depth_stencil_format::d32:
		return
			opengl::color_format(
				GL_DEPTH_COMPONENT
			);
	case renderer::depth_stencil_format::d24s8:
		return
			opengl::color_format(
				GL_DEPTH_STENCIL
			);
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid depth_stencil_format in depth_stencil_to_format!")
	);
}
