//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/optional/deref.hpp>
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
