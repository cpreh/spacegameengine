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
#include "center_on_resize_function.hpp"
#include <sge/renderer/viewport.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::renderer::viewport const
sge::viewport::center_on_resize_function(
	sge::window::dim const &_ref_dim,
	awl::window::event::resize const &_resize
)
{
	return
		viewport::center(
			_ref_dim,
			fcppt::math::dim::structure_cast<
				sge::window::dim
			>(
				_resize.dim()
			)
		);
}
