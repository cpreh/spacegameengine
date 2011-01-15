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


#include "center.hpp"
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/window/dim_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/assert.hpp>

// TODO: reason about all those different size_types!

namespace
{

sge::renderer::pixel_unit
center_position(
	sge::renderer::size_type,
	sge::window::dim_type::value_type
);

}

sge::renderer::viewport const
sge::systems::viewport::center(
	sge::renderer::screen_size const &_screen_size,
	sge::window::dim_type const &_window_dim
)
{
	return
		_screen_size.w()
		> _window_dim.w()
		||
		_screen_size.h()
		> _window_dim.h()
		?
			sge::renderer::viewport(
				sge::renderer::pixel_pos::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_size
				>(
					_window_dim
				)
			)
		:
			sge::renderer::viewport(
				sge::renderer::pixel_pos(
					::center_position(
						_screen_size.w(),
						_window_dim.w()
					),
					::center_position(
						_screen_size.h(),
						_window_dim.h()
					)
				),
				fcppt::math::dim::structure_cast<
					sge::renderer::pixel_size
				>(
					_screen_size
				)
			);
}

namespace
{

sge::renderer::pixel_unit
center_position(
	sge::renderer::size_type const _target_size,
	sge::window::dim_type::value_type const _window_size
)
{
	FCPPT_ASSERT(
		_window_size >= _target_size
	);

	return
		static_cast<
			sge::renderer::pixel_unit
		>
		(
			(
				_window_size
				-
				_target_size
			)
			/ 2u
		);
}

}
