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


#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


sge::viewport::resize_callback
sge::viewport::fill_on_resize()
{
	return
		sge::viewport::resize_callback{
			[](
				awl::window::event::resize const &_resize
			)
			{
				return
					sge::renderer::target::viewport(
						sge::renderer::pixel_rect(
							fcppt::math::vector::null<
								sge::renderer::pixel_rect::vector
							>(),
							fcppt::math::dim::structure_cast<
								sge::renderer::pixel_rect::dim,
								fcppt::cast::to_signed_fun
							>(
								fcppt::math::dim::structure_cast<
									sge::renderer::screen_size,
									fcppt::cast::size_fun
								>(
									_resize.dim()
								)
							)
						)
					);
			}
		};
}
