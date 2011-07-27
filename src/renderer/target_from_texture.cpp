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


#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>

sge::renderer::target_ptr const
sge::renderer::target_from_texture(
	renderer::device &_device,
	renderer::texture::planar &_texture
)
{
	if(
		!(
			_texture.capabilities()
			&
			sge::renderer::texture::capabilities::render_target
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("renderer::target_from_texture() called with a texture ")
			FCPPT_TEXT("that is not a render target!")
		);

	sge::renderer::target_ptr const target(
		_device.create_target()
	);

	target->color_surface(
		_texture.surface(
			renderer::stage(
				0u
			)
		),
		renderer::surface_index(
			0u
		)
	);

	target->viewport(
		renderer::viewport(
			renderer::pixel_rect(
				renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<
					renderer::pixel_rect::dim
				>(
					_texture.size()
				)
			)
		)
	);

	return target;
}
