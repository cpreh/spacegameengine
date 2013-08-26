/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/src/viewport/center.hpp>
#include <sge/window/dim.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


namespace
{

sge::renderer::pixel_unit
center_position(
	sge::window::dim::value_type,
	sge::window::dim::value_type
);

}

sge::renderer::target::viewport const
sge::viewport::center(
	sge::window::dim const &_ref_dim,
	sge::window::dim const &_window_dim
)
{
	return
		_ref_dim.w()
		> _window_dim.w()
		||
		_ref_dim.h()
		> _window_dim.h()
		?
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector::null(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim
					>(
						_window_dim
					)
				)
			)
		:
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector(
						::center_position(
							_ref_dim.w(),
							_window_dim.w()
						),
						::center_position(
							_ref_dim.h(),
							_window_dim.h()
						)
					),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim
					>(
						_ref_dim
					)
				)
			);
}

namespace
{

sge::renderer::pixel_unit
center_position(
	sge::window::dim::value_type const _target_size,
	sge::window::dim::value_type const _window_size
)
{
	FCPPT_ASSERT_PRE(
		_window_size >= _target_size
	);

	return
		fcppt::cast::size<
			sge::renderer::pixel_unit
		>(
			fcppt::cast::to_signed(
				(
					_window_size
					-
					_target_size
				)
				/ 2u
			)
		);
}

}
