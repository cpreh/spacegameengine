//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_depth_stencil_surface.hpp>
#include <sge/d3d9/devicefuncs/set_render_target.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/depth_stencil_offscreen.hpp>
#include <sge/d3d9/surface/optional_d3d_ref.hpp>
#include <sge/d3d9/target/basic_impl.hpp>
#include <sge/d3d9/target/offscreen.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/index_map_impl.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/optional/dynamic_cast.hpp>
#include <fcppt/optional/maybe_void.hpp>


sge::d3d9::target::offscreen::offscreen(
	IDirect3DDevice9 &_device,
	sge::renderer::caps::target_surface_indices const _max_surfaces
)
:
	base(
		_device,
		sge::renderer::target::viewport(
			fcppt::math::box::null<
				sge::renderer::pixel_rect
			>()
		),
		_max_surfaces
	),
	color_surfaces_(),
	depth_stencil_surface_()
{
}

sge::d3d9::target::offscreen::~offscreen()
{
}

void
sge::d3d9::target::offscreen::color_surface(
	sge::renderer::color_buffer::optional_surface_ref const &_surface,
	sge::renderer::target::surface_index const _index
)
{
	color_surfaces_[
		_index.get()
	] =
		fcppt::optional::dynamic_cast_<
			sge::d3d9::surface::color
		>(
			_surface
		);
}

void
sge::d3d9::target::offscreen::depth_stencil_surface(
	sge::renderer::depth_stencil_buffer::optional_surface_ref const &_surface
)
{
	depth_stencil_surface_ =
		fcppt::optional::dynamic_cast_<
			sge::d3d9::surface::depth_stencil_offscreen
		>(
			_surface
		);
}

bool
sge::d3d9::target::offscreen::needs_present() const
{
	return
		false;
}

void
sge::d3d9::target::offscreen::on_activate()
{
	this->change_surfaces(
		true
	);
}

void
sge::d3d9::target::offscreen::on_deactivate()
{
	this->change_surfaces(
		false
	);
}

void
sge::d3d9::target::offscreen::change_surfaces(
	bool const _activate
)
{
	for(
		// Don't deactivate the 0th color surface because D3D9 doesn't allow it
		sge::d3d9::target::offscreen::color_surface_map::size_type const index
		:
		fcppt::make_int_range(
			_activate
			?
				fcppt::literal<
					sge::d3d9::target::offscreen::color_surface_map::size_type
				>(
					0u
				)
			:
				fcppt::literal<
					sge::d3d9::target::offscreen::color_surface_map::size_type
				>(
					1u
				)
			,
			color_surfaces_.impl().size()
		)
	)
		fcppt::optional::maybe_void(
			color_surfaces_[
				index
			],
			[
				_activate,
				index,
				this
			](
				fcppt::reference<
					sge::d3d9::surface::color
				> const _surface
			)
			{
				sge::d3d9::devicefuncs::set_render_target(
					this->device(),
					fcppt::strong_typedef_construct_cast<
						sge::renderer::target::surface_index,
						fcppt::cast::size_fun
					>(
						index
					),
					_activate
					?
						sge::d3d9::surface::optional_d3d_ref(
							fcppt::make_ref(
								_surface.get().surface()
							)
						)
					:
						sge::d3d9::surface::optional_d3d_ref()
				);
			}
		);

	fcppt::optional::maybe_void(
		depth_stencil_surface_,
		[
			_activate,
			this
		](
			fcppt::reference<
				sge::d3d9::surface::depth_stencil_offscreen
			> const _surface
		)
		{
			sge::d3d9::devicefuncs::set_depth_stencil_surface(
				this->device(),
				_activate
				?
					sge::d3d9::surface::optional_d3d_ref(
						fcppt::make_ref(
							_surface.get().surface()
						)
					)
				:
					sge::d3d9::surface::optional_d3d_ref()
			);
		}
	);
}

template
class
sge::d3d9::target::basic<
	sge::renderer::target::offscreen
>;
