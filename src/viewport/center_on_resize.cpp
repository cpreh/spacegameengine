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


#include <sge/renderer/target/viewport.hpp>
#include <sge/src/viewport/center.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::viewport::resize_callback
sge::viewport::center_on_resize(
	sge::window::dim const _dim
)
{
	return
		sge::viewport::resize_callback{
			[
				_dim
			](
				awl::window::event::resize const &_resize
			)
			{
				return
					sge::viewport::center(
						_dim,
						fcppt::math::dim::structure_cast<
							sge::window::dim,
							fcppt::cast::size_fun
						>(
							_resize.dim()
						)
					);
			}
		};
}
