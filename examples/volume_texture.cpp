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


#include <sge/camera/duration.hpp>
#include <sge/camera/movement_speed.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/rotation_speed.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/store.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image3d/box.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/gray8.hpp>
#include <sge/image3d/algorithm/copy_and_convert.hpp>
#include <sge/image3d/algorithm/fill.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/sub.hpp>
#include <sge/image3d/view/to_const.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode3.hpp>
#include <sge/renderer/texture/create_volume_from_view.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/chrono/seconds.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/transform.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cstdlib>

namespace
{

typedef sge::renderer::vf::pos<
	sge::renderer::scalar,
	3
> vf_pos;

typedef sge::renderer::vf::texpos<
	sge::renderer::scalar,
	3
> vf_texpos;

typedef sge::renderer::vf::part<
	boost::mpl::vector2<
		vf_pos,
		vf_texpos
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
	sge::renderer::vertex_buffer &_vertex_buffer,
	pos_array const &_positions
)
{
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

	typedef vf_texpos::packed_type texpos_vector;

	vf_iterator vb_it(
		view.begin()
	);

	for(
		pos_array::const_iterator it(
			_positions.begin()
		);
		it != _positions.end();
		++it
	)
	{
		(*vb_it).set<
			vf_pos
		>(
			*it
		);

		(*vb_it++).set<
			vf_texpos
		>(
			fcppt::math::vector::transform(
				*it,
				::coord_to_texcoord
			)
		);
	}
}

sge::renderer::texture::volume_ptr const
create_texture(
	sge::renderer::device &_device
)
{
	typedef sge::image3d::gray8 store_type;

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
			white_store.view()
		),
		sge::image::colors::white()
	);

	store_type black_store(
		block_size
	);

	sge::image3d::algorithm::fill(
		sge::image3d::view::object(
			black_store.view()
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
				sge::image3d::algorithm::copy_and_convert(
					sge::image3d::view::to_const(
						sge::image3d::view::object(
							(((x + y + z) % 2u) == 0u)
							?
								white_store.view()
							:
								black_store.view()
						)
					),
					sge::image3d::view::sub(
						sge::image3d::view::object(
							whole_store.view()
						),
						sge::image3d::box(
							sge::image3d::box::vector(
								x * block_size.w(),
								y * block_size.h(),
								z * block_size.d()
							),
							block_size
						)
					)
				);
	
	return
		sge::renderer::texture::create_volume_from_view(
			_device,
			sge::image3d::view::to_const(
				sge::image3d::view::object(
					whole_store.view()
				)
			),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::texture::address_mode3(
				sge::renderer::texture::address_mode::clamp
			),
			sge::renderer::resource_flags::none
		);
}

}

int 
main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge volume texture example"),
					sge::window::dim(
						1024,
						768
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d16,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::fill_on_resize()
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				| sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive
				)
			)
		)
		(
			sge::systems::parameterless::font
		)
	);

	sge::renderer::texture::volume_ptr const texture(
		::create_texture(
			sys.renderer()
		)
	);

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vf_format
			>()
		)
	);

	sge::renderer::vertex_buffer_ptr const vertex_buffer(
		sys.renderer().create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::part_index(
				0u
			),
			pos_array::static_size,
			sge::renderer::resource_flags::none
		)
	);

	::fill_geometry(
		*vertex_buffer,
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

	bool running(
		true
	);

	fcppt::signal::scoped_connection const input_connection(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::movement_speed(
				4.0f
			),
			sge::camera::rotation_speed(
				200.0f
			),
			sys.keyboard_collector(),
			sys.mouse_collector()
		)
	);

	fcppt::signal::scoped_connection const viewport_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				fcppt::ref(
					sys.renderer()
				),
				fcppt::ref(
					camera
				),
				sge::renderer::projection::fov(
					fcppt::math::deg_to_rad(
						90.f
					)
				),
				sge::renderer::projection::near(
					0.1f
				),
				sge::renderer::projection::far(
					1000.f
				)
			)
		)
	);

	typedef sge::timer::basic<
		sge::timer::clocks::standard
	> timer;
	
	timer frame_timer(
		timer::parameters(
			fcppt::chrono::seconds(
				1
			)
		)
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		camera.update(
			sge::timer::elapsed_and_reset<
				sge::camera::duration
			>(
				frame_timer
			)
		);

		sge::renderer::scoped_vertex_declaration const scoped_vd(
			sys.renderer(),
			*vertex_declaration
		);

		sge::renderer::scoped_vertex_buffer const scoped_vb(
			sys.renderer(),
			*vertex_buffer
		);

		sge::renderer::texture::scoped const scoped_texture(
			sys.renderer(),
			*texture,
			sge::renderer::stage(
				0u
			)
		);

		sge::renderer::state::scoped const scoped_state(
			sys.renderer(),
			sge::renderer::state::list(
				sge::renderer::state::bool_::clear_back_buffer = true
			)(
				sge::renderer::state::bool_::clear_depth_buffer = true
			)(
				sge::renderer::state::color::back_buffer_clear_color =
					sge::image::colors::black()
			)(
				sge::renderer::state::float_::depth_buffer_clear_val =
					1.0f
			)(
				sge::renderer::state::depth_func::less
			)
		);

		sge::renderer::scoped_block const block(
			sys.renderer()
		);

		sys.renderer().transform(
			sge::renderer::matrix_mode::world,
			camera.world()
		);

		sys.renderer().transform(
			sge::renderer::matrix_mode::projection,
			camera.projection()
		);

		sys.renderer().render_nonindexed(
			sge::renderer::first_vertex(
				0u
			),
			sge::renderer::vertex_count(
				vertex_buffer->size()
			),
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
