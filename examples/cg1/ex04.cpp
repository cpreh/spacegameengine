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


#include <sge/image/color/format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/emissive_color.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/shininess.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/light/attenuation.hpp>
#include <sge/renderer/light/constant_attenuation.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/linear_attenuation.hpp>
#include <sge/renderer/light/object.hpp>
#include <sge/renderer/light/point.hpp>
#include <sge/renderer/light/position.hpp>
#include <sge/renderer/light/quadratic_attenuation.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/time/second_f.hpp>
#include <sge/time/timer.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/quad.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/perspective.hpp>
#include <fcppt/math/matrix/rotation_y.hpp>
#include <fcppt/math/matrix/look_at.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <cmath>
#include <cstdlib>

namespace
{

typedef float float_type;

typedef sge::renderer::vf::pos<
	float_type,
	3
> pos_type;

typedef sge::renderer::vf::normal<
	float_type
> normal_type;

typedef sge::renderer::vf::part<
	boost::mpl::vector2<
		pos_type,
		normal_type
	>
> vertex_main_part;

typedef sge::renderer::vf::format<
	boost::mpl::vector1<
		vertex_main_part
	>
> vertex_format;

typedef sge::renderer::vf::view<
	vertex_main_part
> vertex_view;

typedef vertex_view::iterator vertex_iterator;

typedef vertex_iterator::reference vertex_reference;

void
make_vertex(
	vertex_reference vert,
	float_type const theta,
	float_type const phi
)
{
	typedef pos_type::packed_type vec3;

	vec3 const pos(
		std::sin(theta) * std::cos(phi),
		std::sin(theta) * std::sin(phi),
		std::cos(theta)
	);

	vert.set<pos_type>(
		pos
	);

	vert.set<normal_type>(
		pos
	);
}

}

int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge cg1 ex04"),
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
					sge::renderer::depth_stencil_buffer::d24,
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
				),
				sge::systems::cursor_option_field::null()
			)
		)
	);

	sge::renderer::device &rend(
		sys.renderer()
	);

	float_type const step(
		fcppt::math::twopi<float_type>()
		/ static_cast<float_type>(40)
	);

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		rend.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<
				vertex_format
			>()
		)
	);

	sge::renderer::vertex_buffer_ptr const vb(
		rend.create_vertex_buffer(
			*vertex_declaration,
			sge::renderer::vf::dynamic::part_index(
				0u
			),
			6u
			*
			static_cast<
				sge::renderer::size_type
			>(
				fcppt::math::quad(
					std::ceil(
						fcppt::math::twopi<float_type>()
						/ step
					)
				)
			),
			sge::renderer::resource_flags::none
		)
	);

	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vb,
			sge::renderer::lock_mode::writeonly
		);

		vertex_view const vertices(
			vblock.value()
		);

		float_type shift(0);

		vertex_iterator vb_it = vertices.begin();

		for(
			float_type theta = 0;
			theta < fcppt::math::twopi<float_type>();
			theta += step, shift += step / 2
		)
			for(
				float_type phi = 0;
				phi < fcppt::math::twopi<float_type>();
				phi += step
			)
			{
				float_type const phi_shift(
					phi + shift
				);

				make_vertex(
					*vb_it++,
					theta,
					phi_shift
				);

				make_vertex(
					*vb_it++,
					theta + step,
					phi_shift + step / 2
				);

				make_vertex(
					*vb_it++,
					theta,
					phi_shift + step
				);

				make_vertex(
					*vb_it++,
					theta,
					phi_shift + step
				);

				make_vertex(
					*vb_it++,
					theta + step,
					phi_shift + step / 2.0f
				);

				make_vertex(
					*vb_it++,
					theta + step,
					phi_shift + step * 3.f / 2.f
				);

			}

		FCPPT_ASSERT(vb_it == vertices.end());
	}

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	typedef sge::image::color::rgba32f rgba32f_color;

	rend.state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::bool_::clear_depth_buffer = true)
			(sge::renderer::state::bool_::enable_lighting = true)
			(sge::renderer::state::color::ambient_light_color
				= rgba32f_color(
					(sge::image::color::init::red %= 0.577350269)
					(sge::image::color::init::green %= 0.577350269f)
					(sge::image::color::init::blue %= 0.577350269f)
					(sge::image::color::init::alpha %= 0.)
				)
			)
			(sge::renderer::state::float_::depth_buffer_clear_val = 1.f)
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::black())
			(sge::renderer::state::cull_mode::back)
			(sge::renderer::state::depth_func::less));

	{
		sge::renderer::light::index const light_index(0);

		rend.light(
			light_index,
			sge::renderer::light::object(
				sge::renderer::diffuse_color(
					sge::image::colors::white()
				),
				sge::renderer::specular_color(
					sge::image::colors::white()
				),
				sge::renderer::ambient_color(
					sge::image::colors::white()
				),
				sge::renderer::light::point(
					sge::renderer::light::position(
						sge::renderer::light::position::value_type(
							0.577350269f,
							0.577350269f,
							0.577350269f
						)
					),
					sge::renderer::light::attenuation(
						sge::renderer::light::constant_attenuation(
							1.f
						),
						sge::renderer::light::linear_attenuation(
							0.f
						),
						sge::renderer::light::quadratic_attenuation(
							0.f
						)
					)
				)
			)
		);

		rend.enable_light(
			light_index,
			true
		);
	}

	rend.material(
		sge::renderer::material(
			sge::renderer::diffuse_color(
				rgba32f_color(
					(sge::image::color::init::red %= 0.1)
					(sge::image::color::init::green %= 0.1)
					(sge::image::color::init::blue %= 0.1)
					(sge::image::color::init::alpha %= 1.)
				)
			),
			sge::renderer::ambient_color(
				rgba32f_color(
					(sge::image::color::init::red %= 0.75)
					(sge::image::color::init::green %= 0.75)
					(sge::image::color::init::blue %= 1.)
					(sge::image::color::init::alpha %= 1.)
				)
			),
			sge::renderer::specular_color(
				rgba32f_color(
					(sge::image::color::init::red %= 0.5)
					(sge::image::color::init::green %= 0.5)
					(sge::image::color::init::blue %= 0.5)
					(sge::image::color::init::alpha %= 1.)
				)
			),
			sge::renderer::emissive_color(
				sge::image::colors::black()
			),
			sge::renderer::shininess(
				100.f
			)
		)
	);

	sge::time::timer rotation_time(
		sge::time::second_f(
			0.1f
		)
	);

	float_type angle(0);

	sge::renderer::scoped_vertex_declaration const scoped_declaration(
		rend,
		*vertex_declaration
	);

	sge::renderer::scoped_vertex_buffer const scoped_vb(
		rend,
		*vb
	);

	while(
		running
	)
	{
		sys.window().dispatch();

		rend.transform(
			sge::renderer::matrix_mode::projection,
			fcppt::math::matrix::perspective(
				sge::renderer::aspect(
					fcppt::math::dim::structure_cast<
						sge::renderer::screen_size
					>(
						sys.window().size()
					)
				),
				fcppt::math::pi<float_type>() / 2,
				static_cast<float_type>(1),
				static_cast<float_type>(256)
			)
		);


		angle += fcppt::math::twopi<float_type>() * rotation_time.update();

		{
			typedef fcppt::math::vector::static_<
				float_type,
				3
			>::type vec3;

			rend.transform(
				sge::renderer::matrix_mode::world,
				fcppt::math::matrix::rotation_y(
					angle
				)
				*
				fcppt::math::matrix::look_at(
					vec3(
						0,
						0,
						3
					),
					vec3::null(),
					vec3(
						0,
						1,
						0
					)
				)
			);
		}

		sge::renderer::scoped_block const block(
			rend
		);

		rend.render_nonindexed(
			sge::renderer::first_vertex(0),
			sge::renderer::vertex_count(
				vb->size()
			),
			sge::renderer::nonindexed_primitive_type::triangle
		);
	}
}
catch(
	std::exception const &_exception
)
{
	std::cerr << _exception.what() << '\n';

	return EXIT_FAILURE;
}
