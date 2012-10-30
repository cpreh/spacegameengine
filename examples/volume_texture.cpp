/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/perspective_projection_from_viewport.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/store.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image3d/box.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/l8.hpp>
#include <sge/image3d/algorithm/copy.hpp>
#include <sge/image3d/algorithm/fill.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/sub.hpp>
#include <sge/image3d/view/to_const.hpp>
#include <sge/noise/sample.hpp>
#include <sge/noise/sample_parameters.hpp>
#include <sge/noise/simplex/object.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_declaration_scoped_ptr.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off.hpp>
#include <sge/renderer/state/core/sampler/const_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/default.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_volume_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_scoped_ptr.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/mouse_collector.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_map.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/assign/make_map.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef sge::renderer::vf::pos<
	sge::renderer::scalar,
	3
> vf_pos;

typedef sge::renderer::vf::texpos<
	sge::renderer::scalar,
	3,
	sge::renderer::vf::index<
		0
	>
> vf_texpos0;

typedef sge::renderer::vf::texpos<
	sge::renderer::scalar,
	3,
	sge::renderer::vf::index<
		1
	>
> vf_texpos1;

typedef sge::renderer::vf::part<
	boost::mpl::vector3<
		vf_pos,
		vf_texpos0,
		vf_texpos1
	>
> vf_part;

typedef sge::renderer::vf::format<
	boost::mpl::vector1<
		vf_part
	>
> vf_format;

typedef vf_pos::packed_type pos_vector;

typedef fcppt::container::array<
	pos_vector,
	2 * 3 * 6
> pos_array;

sge::renderer::scalar
coord_to_texcoord(
	sge::renderer::scalar const _value
)
{
	return
		static_cast<
			sge::renderer::scalar
		>(
			(_value + 1.f) / 2.f
		);
}

void
fill_geometry(
	sge::renderer::vertex_buffer &_vertex_buffer
)
{
	pos_array const positions(
		fcppt::assign::make_array<
			pos_vector
		>
		// bottom 1
		(
			pos_vector(
				-1,-1,-1
			)
		)(
			pos_vector(
				-1,-1,1
			)
		)(
			pos_vector(
				1,-1,1
			)
		)
		// bottom 2
		(
			pos_vector(
				1,-1,1
			)
		)(
			pos_vector(
				1,-1,-1
			)
		)(
			pos_vector(
				-1,-1,-1
			)
		)
		// top 1
		(
			pos_vector(
				-1,1,-1
			)
		)(
			pos_vector(
				1,1,-1
			)
		)(
			pos_vector(
				1,1,1
			)
		)
		// top 2
		(
			pos_vector(
				1,1,1
			)
		)(
			pos_vector(
				-1,1,1
			)
		)(
			pos_vector(
				-1,1,-1
			)
		)
		// left 1
		(
			pos_vector(
				-1,-1,-1
			)
		)(
			pos_vector(
				-1,1,-1
			)
		)(
			pos_vector(
				-1,1,1
			)
		)
		// left 2
		(
			pos_vector(
				-1,1,1
			)
		)(
			pos_vector(
				-1,-1,1
			)
		)(
			pos_vector(
				-1,-1,-1
			)
		)
		// right 1
		(
			pos_vector(
				1,-1,-1
			)
		)(
			pos_vector(
				1,-1,1
			)
		)(
			pos_vector(
				1,1,1
			)
		)
		// right 2
		(
			pos_vector(
				1,1,1
			)
		)(
			pos_vector(
				1,1,-1
			)
		)(
			pos_vector(
				1,-1,-1
			)
		)
		// front 1
		(
			pos_vector(
				-1,-1,1
			)
		)(
			pos_vector(
				-1,1,1
			)
		)(
			pos_vector(
				1,1,1
			)
		)
		// front 2
		(
			pos_vector(
				1,1,1
			)
		)(
			pos_vector(
				1,-1,1
			)
		)(
			pos_vector(
				-1,-1,1
			)
		)
		// back 1
		(
			pos_vector(
				-1,-1,-1
			)
		)(
			pos_vector(
				1,-1,-1
			)
		)(
			pos_vector(
				1,1,-1
			)
		)
		// back 2
		(
			pos_vector(
				1,1,-1
			)
		)(
			pos_vector(
				-1,1,-1
			)
		)(
			pos_vector(
				-1,-1,-1
			)
		)
	);

	sge::renderer::scoped_vertex_lock const vb_lock(
		_vertex_buffer,
		sge::renderer::lock_mode::writeonly
	);

	typedef sge::renderer::vf::view<
		vf_part
	> vf_view;

	vf_view const view(
		vb_lock.value()
	);

	typedef vf_view::iterator vf_iterator;

	vf_iterator vb_it(
		view.begin()
	);

	for(
		pos_array::const_iterator it(
			positions.begin()
		);
		it != positions.end();
		++it
	)
	{
		(*vb_it).set<
			vf_pos
		>(
			*it
		);

		pos_vector const texpos(
			fcppt::algorithm::array_map<pos_vector>(
				*it,
				coord_to_texcoord
			)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos
		);
	}
}

sge::renderer::texture::volume_unique_ptr
create_noise_texture(
	sge::renderer::device::core &_device)
{
	typedef
	sge::image3d::l8
	store_type;

	typedef
	store_type::view_type
	view_type;

	typedef
	sge::noise::simplex::object<float,3>
	noise_type;

	typedef
	sge::noise::sample_parameters<noise_type>
	param_type;

	noise_type noise_generator(
		sge::noise::simplex::width(
			128u));

	typedef
	view_type::dim
	dim_type;

	typedef
	dim_type::value_type
	dim_value_type;

	store_type s(
		store_type::dim(
			128,
			128,
			128));

	view_type view(
		s.view());

	for(dim_value_type z = 0; z < view.size()[2]; ++z)
	{
		for(dim_value_type y = 0; y < view.size()[1]; ++y)
		{
			for(dim_value_type x = 0; x < view.size()[0]; ++x)
			{
				dim_type const current_position(
					x,
					y,
					z);

				view[current_position].set(
					mizuiro::color::channel::luminance(),
					static_cast<sge::image::color::channel8>(
						256.0f *
						(0.5f + 0.5f *
						sge::noise::sample(
							noise_generator,
							param_type(
								param_type::position_type(
									noise_type::vector_type(
										static_cast<noise_type::value_type>(
											x),
										static_cast<noise_type::value_type>(
											y),
										static_cast<noise_type::value_type>(
											z))),
								param_type::amplitude_type(
									0.8f),
								param_type::frequency_type(
									.005f),
								param_type::octaves_type(
									6u))))));
			}
		}
	}

	return
		sge::renderer::texture::create_volume_from_view(
			_device,
			sge::image3d::view::to_const(
				sge::image3d::view::object(
					s.wrapped_view())),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no);
}

sge::renderer::texture::volume_unique_ptr
create_checkers_texture(
	sge::renderer::device::core &_device
)
{
	typedef sge::image3d::l8 store_type;

	sge::image::size_type const block_element_size(
		4u
	);

	sge::image3d::dim const block_size(
		block_element_size,
		block_element_size,
		block_element_size
	);

	sge::image::size_type const num_blocks(
		16u
	);

	store_type whole_store(
		block_size * num_blocks
	);

	store_type white_store(
		block_size
	);

	sge::image3d::algorithm::fill(
		sge::image3d::view::object(
			white_store.wrapped_view()
		),
		sge::image::colors::white()
	);

	store_type black_store(
		block_size
	);

	sge::image3d::algorithm::fill(
		sge::image3d::view::object(
			black_store.wrapped_view()
		),
		sge::image::colors::black()
	);

	for(
		sge::image::size_type z = 0;
		z < num_blocks;
		++z
	)
		for(
			sge::image::size_type y = 0;
			y < num_blocks;
			++y
		)
			for(
				sge::image::size_type x = 0;
				x < num_blocks;
				++x
			)
				sge::image3d::algorithm::copy(
					sge::image3d::view::to_const(
						sge::image3d::view::object(
							(((x + y + z) % 2u) == 0u)
							?
								white_store.wrapped_view()
							:
								black_store.wrapped_view()
						)
					),
					sge::image3d::view::sub(
						sge::image3d::view::object(
							whole_store.wrapped_view()
						),
						sge::image3d::box(
							sge::image3d::box::vector(
								x * block_size.w(),
								y * block_size.h(),
								z * block_size.d()
							),
							block_size
						)
					),
					sge::image::algorithm::may_overlap::no
				);

	return
		sge::renderer::texture::create_volume_from_view(
			_device,
			sge::image3d::view::to_const(
				sge::image3d::view::object(
					whole_store.wrapped_view()
				)
			),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::no
		);
}

}

awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		boost::mpl::vector3<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::keyboard_collector,
					sge::systems::mouse_collector
				>
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge volume texture example")
					),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::d16,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
	);

	sge::renderer::texture::volume_scoped_ptr const texture(
		create_noise_texture(
			sys.renderer_core()
		)
	);

	sge::renderer::vertex_declaration_scoped_ptr const vertex_declaration(
		sys.renderer_core().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vf_format
			>()
		)
	);

	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer(
		sys.renderer_core().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::make_part_index<
				vf_format,
				vf_part
			>(),
			sge::renderer::vertex_count(
				pos_array::dim_wrapper::value
			),
			sge::renderer::resource_flags_field::null()
		)
	);

	::fill_geometry(
		*vertex_buffer
	);

	fcppt::signal::scoped_connection const input_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	sge::camera::first_person::object camera(
		sge::camera::first_person::parameters(
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::first_person::is_active(
				true
			),
			sge::camera::first_person::movement_speed(
				4.0f
			),
			sge::camera::coordinate_system::identity()
		)
	);

	sge::camera::perspective_projection_from_viewport camera_viewport_connection(
		camera,
		sys.viewport_manager(),
		sge::renderer::projection::near(
			0.1f
		),
		sge::renderer::projection::far(
			1000.f
		),
		sge::renderer::projection::fov(
			fcppt::math::deg_to_rad(
				90.f
			)
		)
	);

	typedef sge::timer::basic<
		sge::timer::clocks::standard
	> timer;

	timer frame_timer(
		timer::parameters(
			boost::chrono::seconds(
				1
			)
		)
	);

	sge::renderer::state::core::depth_stencil::object_scoped_ptr const depth_stencil_state(
		sys.renderer_core().create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				sge::renderer::state::core::depth_stencil::depth::enabled(
					sge::renderer::state::core::depth_stencil::depth::func::less,
					sge::renderer::state::core::depth_stencil::depth::write_enable(
						true
					)
				),
				sge::renderer::state::core::depth_stencil::stencil::off()
			)
		)
	);

	sge::renderer::state::core::sampler::object_scoped_ptr const sampler_state(
		sys.renderer_core().create_sampler_state(
			sge::renderer::state::core::sampler::parameters(
				sge::renderer::state::core::sampler::address::mode_all(
					sge::renderer::state::core::sampler::address::mode::clamp
				),
				sge::renderer::state::core::sampler::filter::default_()
			)
		)
	);

	sge::renderer::state::core::sampler::const_object_ref_map const samplers(
		fcppt::assign::make_map<
			sge::renderer::state::core::sampler::const_object_ref_map
		>(
			sge::renderer::texture::stage(
				0u
			),
			fcppt::cref(
				*sampler_state
			)
		)(
			sge::renderer::texture::stage(
				1u
			),
			fcppt::cref(
				*sampler_state
			)
		)
	);

	while(
		sys.window_system().poll()
	)
	{
		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::update_duration
			>(
				frame_timer
			)
		);

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		sge::renderer::scoped_vertex_declaration const scoped_vd(
			scoped_block.get(),
			*vertex_declaration
		);

		sge::renderer::scoped_vertex_buffer const scoped_vb(
			scoped_block.get(),
			*vertex_buffer
		);

		sge::renderer::texture::scoped const scoped_texture1(
			scoped_block.get(),
			*texture,
			sge::renderer::texture::stage(
				0u
			)
		);

		sge::renderer::texture::scoped const scoped_texture2(
			scoped_block.get(),
			*texture,
			sge::renderer::texture::stage(
				1u
			)
		);

		sge::renderer::state::core::depth_stencil::scoped const scoped_depth_stencil(
			scoped_block.get(),
			*depth_stencil_state
		);

		sge::renderer::state::core::sampler::scoped const scoped_sampler(
			scoped_block.get(),
			samplers
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
			.depth_buffer(
				1.f
			)
		);

		sge::renderer::state::ffp::transform::object_scoped_ptr const projection_state(
			sys.renderer_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					camera.projection_matrix().get()
				)
			)
		);

		sge::renderer::state::ffp::transform::object_scoped_ptr const world_state(
			sys.renderer_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					sge::camera::matrix_conversion::world(
						camera.coordinate_system()
					)
				)
			)
		);

		sge::renderer::state::ffp::transform::scoped const projection_transform(
			scoped_block.get(),
			sge::renderer::state::ffp::transform::mode::projection,
			*projection_state
		);

		sge::renderer::state::ffp::transform::scoped const world_transform(
			scoped_block.get(),
			sge::renderer::state::ffp::transform::mode::world,
			*world_state
		);

		scoped_block.get().render_nonindexed(
			sge::renderer::first_vertex(
				0u
			),
			sge::renderer::vertex_count(
				vertex_buffer->size()
			),
			sge::renderer::primitive_type::triangle_list
		);
	}

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
