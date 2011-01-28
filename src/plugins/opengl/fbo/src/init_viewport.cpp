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


#include "../init_viewport.hpp"
#include "../../depth_stencil_texture.hpp"
#include "../../texture.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>

sge::renderer::viewport const
sge::opengl::fbo::init_viewport(
	sge::opengl::texture_ptr const _texture,
	sge::opengl::depth_stencil_texture_ptr const _depth_stencil_texture
)
{
	if(
		!_texture
		&& !_depth_stencil_texture
	)
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Both texture and depth_stencil_texture are null in a render target!")
		);

		return
			sge::renderer::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					sge::renderer::pixel_rect::dim::null()
				)
			);
	}

	return
		sge::renderer::viewport(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_rect::dim
				>(
					_texture
					?
						_texture->dim()
					:
						_depth_stencil_texture->dim()
				)
			)
		);
}
