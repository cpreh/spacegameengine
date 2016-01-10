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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/get_render_target.hpp>
#include <sge/d3d9/devicefuncs/set_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/target/temporary.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>


sge::d3d9::target::temporary::temporary(
	IDirect3DDevice9 &_device,
	sge::renderer::caps::target_surface_indices const _surfaces
)
:
	device_(
		_device
	),
	depth_stencil_surface_(
		sge::d3d9::devicefuncs::get_depth_stencil_surface(
			_device
		)
	),
	color_surfaces_(
		fcppt::algorithm::map<
			sge::d3d9::target::temporary::scoped_surface_vector
		>(
			fcppt::make_int_range_count(
				sge::renderer::target::surface_index(
					_surfaces.get()
				)
			),
			[
				&_device
			](
				sge::renderer::target::surface_index const _index
			)
			{
				return
					sge::d3d9::devicefuncs::get_render_target(
						_device,
						_index
					);
			}
		)
	)
{
}

sge::d3d9::target::temporary::~temporary()
{
	sge::d3d9::devicefuncs::set_depth_stencil_surface(
		device_,
		fcppt::optional::deref(
			depth_stencil_surface_
		)
	);

	for(
		auto const index
		:
		fcppt::make_int_range_count(
			color_surfaces_.size()
		)
	)
		sge::d3d9::devicefuncs::set_render_target(
			device_,
			fcppt::strong_typedef_construct_cast<
				sge::renderer::target::surface_index,
				fcppt::cast::size_fun
			>(
				index
			),
			fcppt::optional::deref(
				color_surfaces_[
					index
				]
			)
		);
}
