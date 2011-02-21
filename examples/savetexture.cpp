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


#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/window/instance.hpp>
#include <sge/config/media_path.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/target_from_texture.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/const_scoped_planar_lock.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/log/global.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object_impl.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/image2d/loader.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_depth.hpp>
#include <sge/sprite/with_dim.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/shader/vf_to_string.hpp>
#include <sge/shader/object.hpp>
#include <sge/shader/variable.hpp>
#include <sge/shader/variable_type.hpp>
#include <sge/shader/sampler.hpp>
#include <sge/shader/scoped.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/systems/viewport/center_on_resize.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/exception.hpp>
#include <sge/extension_set.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/make_unspecified_tag.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/view.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/nonassignable.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>
#include <cstdlib>

namespace
{
namespace screen_vf
{
namespace tags
{
SGE_RENDERER_VF_MAKE_UNSPECIFIED_TAG(position)
}

typedef 
sge::renderer::vf::unspecified
<
	sge::renderer::vf::vector
	<
		sge::renderer::scalar,
		2
	>,
	tags::position
> 
position;
}
namespace screen_vf
{
typedef 
sge::renderer::vf::format
<
	boost::mpl::vector1
	<
		position
	>
> 
format;
}
namespace screen_vf
{
typedef 
sge::renderer::vf::view
<
	format
> 
vertex_view;
}
namespace screen_vf
{
sge::renderer::vertex_buffer_ptr const
create_quad(
	sge::shader::object &shader,
	sge::renderer::device_ptr const renderer)
{
	sge::renderer::vertex_buffer_ptr const vb(
		renderer->create_vertex_buffer(
			sge::renderer::vf::dynamic::make_format<format>(),
			static_cast<sge::renderer::size_type>(
				6),
			sge::renderer::resource_flags::none));
	
	sge::shader::scoped scoped_shader(
		shader);
	
	sge::renderer::scoped_vertex_buffer const scoped_vb_(
		renderer,
		vb);

	sge::renderer::scoped_vertex_lock const vblock(
		vb,
		sge::renderer::lock_mode::writeonly);

	vertex_view const vertices(
		vblock.value());

	vertex_view::iterator vb_it(
		vertices.begin());

	// Left top
	(vb_it++)->set<position>(
		position::packed_type(
			-1, 1));

	// Left bottom
	(vb_it++)->set<position>(
		position::packed_type(
			-1,-1));

	// Right top
	(vb_it++)->set<position>(
		position::packed_type(
			1,1));

	// Right top
	(vb_it++)->set<position>(
		position::packed_type(
			1,1));

	// Left bottom
	(vb_it++)->set<position>(
		position::packed_type(
			-1,-1));

	// Right bottom
	(vb_it++)->set<position>(
		position::packed_type(
			1,-1));

	return vb;
}
}

#if 0
typedef 
sge::image::color::rgba8_format 
sprite_color;

typedef 
sge::sprite::choices
<
	sge::sprite::type_choices
	<
		int,
		float,
		sprite_color
	>,
	boost::mpl::vector4
	<
		sge::sprite::with_color,
		sge::sprite::with_texture,
		sge::sprite::with_depth,
		sge::sprite::with_dim
	> 
> 
sprite_choices;

typedef 
sge::sprite::object
<
	sprite_choices
> 
sprite_object;

typedef 
sge::sprite::system
<
	sprite_choices
>::type 
sprite_system;

typedef 
sge::sprite::parameters
<
	sprite_choices
> 
sprite_parameters;

class sprite_functor
{
FCPPT_NONASSIGNABLE(sprite_functor)
public:
	explicit 
	sprite_functor(
		sprite_object &_sprite)
	:
		sprite_(
			_sprite)
	{}

	void
	operator()(
		sge::input::mouse::axis_event const &k) const
	{
		switch (k.axis())
		{
		case sge::input::mouse::axis::x:
			sprite_.x(
				static_cast<sprite_object::unit>(
					sprite_.x() + k.axis_value())
			);

			break;
		case sge::input::mouse::axis::y:
			sprite_.y(
				static_cast<sprite_object::unit>(
					sprite_.y() + k.axis_value()));
			break;
		default:
			break;
		}
	}
private:
	sprite_object &sprite_;
};
#endif
}

int main(
	int argc,
	char *argv[])
try
{
	if (argc != 2)
	{
		std::cerr << "usage: " << argv[0] << " <output-file>\n";
		return EXIT_FAILURE;
	}

	fcppt::log::activate_levels(
		sge::log::global(),
		fcppt::log::level::debug);

	sge::window::dim const window_dim(
		1024,
		768);

	sge::systems::instance sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("sge save texture example"),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_buffer::off,
					sge::renderer::stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::systems::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector) | 
					sge::systems::input_helper::mouse_collector,
				sge::systems::cursor_option_field::null()))
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				fcppt::assign::make_container<sge::extension_set>(
					FCPPT_TEXT("png")))));

	sge::renderer::texture::planar_ptr target_texture(
		sys.renderer()->create_planar_texture(
			sge::renderer::texture::planar_parameters(
				fcppt::math::dim::structure_cast<sge::renderer::dim2>(
					window_dim
				),
				sge::image::color::format::rgb8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::clamp),
				sge::renderer::resource_flags_field(
					sge::renderer::resource_flags::readable))));

	sge::renderer::target_ptr const temp_target(
		sge::renderer::target_from_texture(
			sys.renderer(),
			target_texture
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(running))));

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black()));

	sge::shader::object shader_(
		sys.renderer(),
		sge::config::media_path()/FCPPT_TEXT("shaders")/FCPPT_TEXT("copy_vertex.glsl"),
		sge::config::media_path()/FCPPT_TEXT("shaders")/FCPPT_TEXT("copy_fragment.glsl"),
		sge::shader::vf_to_string<screen_vf::format>(),
		fcppt::assign::make_container<sge::shader::variable_sequence>(
			sge::shader::variable(
				"target_size",
				sge::shader::variable_type::const_,
				fcppt::math::dim::structure_cast<sge::renderer::vector2>(
					window_dim))),
		fcppt::assign::make_container<sge::shader::sampler_sequence>(
			sge::shader::sampler(
				"tex",
				sge::renderer::texture::planar_ptr())));

	sge::renderer::vertex_buffer_ptr const quad_(
		screen_vf::create_quad(
			shader_,
			sys.renderer()));

	{
		sge::renderer::scoped_target scoped_target(
			sys.renderer(),
			temp_target);

		sge::renderer::scoped_block scoped_block(
			sys.renderer());

		sge::shader::scoped scoped_shader(
			shader_);

		sge::renderer::scoped_vertex_buffer const scoped_vb_(
			sys.renderer(),
			quad_);

		sys.renderer()->render(
			sge::renderer::first_vertex(
				0),
			sge::renderer::vertex_count(
				quad_->size()),
			sge::renderer::nonindexed_primitive_type::triangle);
	}

	sge::renderer::texture::const_scoped_planar_lock slock(
		target_texture);

	sys.image_loader().loaders().at(0)->create(
		slock.value())->save(
		fcppt::from_std_string(
			argv[1]));
}
catch(sge::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	std::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
