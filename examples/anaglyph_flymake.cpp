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

#include <sge/camera/activation_state.hpp>
#include <sge/camera/identity_gizmo.hpp>
#include <sge/camera/object.hpp>
#include <sge/camera/parameters.hpp>
#include <sge/camera/projection/object.hpp>
#include <sge/camera/projection/update_perspective_from_viewport.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/model/index_sequence.hpp>
#include <sge/model/loader.hpp>
#include <sge/model/object.hpp>
#include <sge/model/vertex_sequence.hpp>
#include <sge/model/index_sequence.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/size_type.hpp>
// Yeah, I probably shouldn't include this.
#include <sge/renderer/state/state.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/object_parameters.hpp>
#include <sge/shader/activate_everything.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/scoped.hpp>
#include <sge/shader/sampler.hpp>
#include <sge/shader/variable.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/shader/vf_to_string.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/systems/window.hpp>
#include <sge/time/second.hpp>
#include <sge/time/timer.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/window/simple_parameters.hpp>
#include <sge/log/global.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/bitfield.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/log/log.hpp>
#include <fcppt/math/deg_to_rad.hpp>
#include <fcppt/math/dim/dim.hpp>
#include <fcppt/math/matrix/matrix.hpp>
#include <fcppt/math/vector/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/signal/signal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>

/**
	Example description:


	This example shows the usage of:

 */


namespace
{
namespace vf
{
typedef 
sge::renderer::vf::pos
<
	// type and dimension of the position attribute values from 1 to 4 are possible
	sge::renderer::scalar,
	3
> 
position;

typedef 
sge::renderer::vf::part
<
	boost::mpl::vector1
	<
		position
	>
> 
format_part;

typedef 
sge::renderer::vf::format
<
	boost::mpl::vector1<format_part>
> 
format;

typedef
sge::renderer::vf::view<format_part>
format_part_view;
}

class compiled_model
{
FCPPT_NONCOPYABLE(
	compiled_model);
public:
	explicit
	compiled_model(
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &,
		sge::model::object const &);

	void
	render();

	~compiled_model();
private:
	sge::renderer::device &renderer_;
	sge::renderer::vertex_buffer_ptr const vb_;
	sge::renderer::index_buffer_ptr const ib_;
};

compiled_model::compiled_model(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration const &_vd,
	sge::model::object const &_model)
:
	renderer_(
		_renderer),
	vb_(
		renderer_.create_vertex_buffer(
			_vd,
			sge::renderer::vf::dynamic::part_index(
				0u),
			static_cast<sge::renderer::size_type>(
				_model.vertices(_model.part_names().front()).size()),
			sge::renderer::resource_flags::none)),
	ib_(
		renderer_.create_index_buffer(
			sge::renderer::index::dynamic::format::i16,
			static_cast<sge::renderer::size_type>(
				_model.indices(_model.part_names().front()).size()),
		sge::renderer::resource_flags::none))
{
	{
		sge::renderer::scoped_vertex_lock const vblock(
			*vb_,
			sge::renderer::lock_mode::writeonly);

		vf::format_part_view const current_vertex_view(
			vblock.value());

		vf::format_part_view::iterator current_vertex(
			current_vertex_view.begin());

		typedef 
		vf::position::packed_type 
		position_vector;

		sge::model::vertex_sequence const model_vertices = 
			_model.vertices(
				_model.part_names().front());

		for(
			sge::model::vertex_sequence::const_iterator current_model_vertex = 
				model_vertices.begin();
			current_model_vertex != model_vertices.end();
			++current_model_vertex)
			(*current_vertex++).set<vf::position>(
				fcppt::math::vector::structure_cast<position_vector>(
					*current_model_vertex));
	}

	sge::renderer::scoped_index_lock const iblock(
		*ib_,
		sge::renderer::lock_mode::writeonly);

	sge::renderer::index::dynamic::view const indices(
		iblock.value());

	sge::renderer::index::iterator<sge::renderer::index::format_16> current_index(
		indices.data());

	sge::model::index_sequence const model_indices = 
		_model.indices(
			_model.part_names().front());

	for(
		sge::model::index_sequence::const_iterator current_model_index = 
			model_indices.begin();
		current_model_index != model_indices.end();
		++current_model_index)
		(*current_index++).set(
			static_cast<sge::renderer::index::i16>(
				*current_model_index));
}

void
compiled_model::render()
{
	renderer_.render_nonindexed(
		sge::renderer::first_vertex(0),
		sge::renderer::vertex_count(
			vb_->size()),
		sge::renderer::nonindexed_primitive_type::triangle);
}

compiled_model::~compiled_model()
{
}

void
create_back_texture(
	sge::renderer::device &renderer,
	sge::shader::object &shader,
	sge::renderer::target_ptr &target)
{
	sge::renderer::texture::planar_ptr target_texture(
		renderer.create_planar_texture(
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<sge::renderer::dim2>(
					sge::renderer::viewport_size(
						renderer)),
				sge::image::color::format::rgb8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags::none,
				sge::renderer::texture::capabilities_field(
					sge::renderer::texture::capabilities::render_target))));

	target = 
		sge::renderer::target_from_texture(
			renderer,
			*target_texture);

	shader.update_texture(
		"first_pass_texture",
		target_texture);
}
}

int 
main()
try
{
	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::systems::instance sys(
		sge::systems::list()
			(sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge test for anaglyph 3D"),
					sge::window::dim(1024,768))))
			(sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::d24,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling),
				sge::viewport::fill_on_resize()))
			(sge::systems::parameterless::md3_loader)
			(sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field(
					sge::systems::cursor_option::exclusive))));

	bool running = 
		true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running))));

	sge::camera::object camera(
		sge::camera::parameters(
			sge::camera::projection::object(),
			static_cast<sge::renderer::scalar>(4.),
			static_cast<sge::renderer::scalar>(200.),
			sge::camera::identity_gizmo(),
			sys.keyboard_collector(),
			sys.mouse_collector(),
			sge::camera::activation_state::active));

	// Adapt the camera to the viewport
	fcppt::signal::scoped_connection const viewport_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				sge::camera::projection::update_perspective_from_viewport,
				fcppt::ref(
					sys.renderer()),
				fcppt::ref(
					camera),
				// Field of view
				static_cast<sge::renderer::scalar>(
					fcppt::math::deg_to_rad(
						90.)),
				// Near plane
				static_cast<sge::renderer::scalar>(
					0.1),
				// Far plane
				static_cast<sge::renderer::scalar>(
					1000.))));

	sge::renderer::vertex_declaration_ptr const vertex_declaration(
		sys.renderer().create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<vf::format>()));

	sge::shader::object first_pass_shader(
		sge::shader::object_parameters(
			sys.renderer(),
			*vertex_declaration,
			sge::config::media_path() 
				/ FCPPT_TEXT("shaders")
				/ FCPPT_TEXT("anaglyph")
				/ FCPPT_TEXT("first_pass_vertex.glsl"),
			sge::config::media_path() 
				/ FCPPT_TEXT("shaders")
				/ FCPPT_TEXT("anaglyph")
				/ FCPPT_TEXT("first_pass_fragment.glsl"),
			sge::shader::vf_to_string<vf::format>(),
			fcppt::assign::make_container<sge::shader::variable_sequence>
				(sge::shader::variable(
					"mvp",
					sge::shader::variable_type::uniform,
					sge::renderer::matrix4::identity())),
			sge::shader::sampler_sequence()));

	sge::shader::object second_pass_shader(
		sge::shader::object_parameters(
			sys.renderer(),
			*vertex_declaration,
			sge::config::media_path() 
				/ FCPPT_TEXT("shaders")
				/ FCPPT_TEXT("anaglyph")
				/ FCPPT_TEXT("second_pass_vertex.glsl"),
			sge::config::media_path() 
				/ FCPPT_TEXT("shaders")
				/ FCPPT_TEXT("anaglyph")
				/ FCPPT_TEXT("second_pass_fragment.glsl"),
			sge::shader::vf_to_string<vf::format>(),
			fcppt::assign::make_container<sge::shader::variable_sequence>
				(sge::shader::variable(
					"mvp",
					sge::shader::variable_type::uniform,
					sge::renderer::matrix4::identity())),
			fcppt::assign::make_container<sge::shader::sampler_sequence>(
				sge::shader::sampler(
					"first_pass_texture",
					sge::renderer::texture::planar_ptr()))));

	sge::renderer::target_ptr temp_target;

	fcppt::signal::scoped_connection create_back_texture_connection(
		sys.viewport_manager().manage_callback(
			std::tr1::bind(
				&create_back_texture,
				fcppt::ref(
					sys.renderer()),
				fcppt::ref(
					second_pass_shader),
				fcppt::ref(
					temp_target))));

	compiled_model main_model(
		sys.renderer(),
		*vertex_declaration,
		*sys.md3_loader().load(
			sge::config::media_path()
				/ FCPPT_TEXT("models") 
				/ FCPPT_TEXT("european_fnt_v2.md3")));

	// Some render states
	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::bool_::clear_depth_buffer = true)
			(sge::renderer::state::float_::depth_buffer_clear_val = 1.f)
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::bool_::enable_alpha_blending = false)
			(sge::renderer::state::cull_mode::off)
			(sge::renderer::state::draw_mode::line)
			(sge::renderer::state::stencil_func::off)
			(sge::renderer::state::color::back_buffer_clear_color = 
				sge::image::colors::black()));

	sge::time::timer 
		frame_timer(
			sge::time::second(
				1));

	while(running)
	{
		sys.window().dispatch();

		camera.update(
			frame_timer.reset());

		if(!temp_target)
			continue;

		{
			sge::renderer::scoped_target const target_(
				sys.renderer(),
				*temp_target);

			sge::renderer::scoped_block const block_(
				sys.renderer());

			sge::shader::scoped scoped_shader(
				first_pass_shader,
				sge::shader::activate_everything());

			first_pass_shader.update_uniform(
				"mvp",
				camera.mvp());

			main_model.render();	
		}

		// Next up: 
		// - move camera

		sge::renderer::scoped_block const block_(
			sys.renderer());

		sge::shader::scoped scoped_shader(
			second_pass_shader,
			sge::shader::activate_everything());

		second_pass_shader.update_uniform(
			"mvp",
			camera.mvp());

		

		main_model.render();	
	}
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
