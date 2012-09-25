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


#include <sge/bvh/dummy_node.hpp>
#include <sge/bvh/object_impl.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image/colors.hpp>
#include <sge/image/color/rgba8_from_hex_string.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/input_helper.hpp>
#include <sge/systems/input_helper_field.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/tree/depth.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_int.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono.hpp>
#include <example_main.hpp>
#include <exception>
#include <iostream>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{
typedef sge::sprite::config::choices<
	sge::sprite::config::type_choices<
		sge::sprite::config::unit_type<
			sge::renderer::scalar
		>,
		sge::sprite::config::float_type<
			sge::renderer::scalar
		>
	>,
	sge::sprite::config::normal_size,
	boost::mpl::vector1<
		sge::sprite::config::with_color<
			sge::image::color::rgba8_format
		>
	>
> sprite_choices;

typedef sge::sprite::buffers::with_declaration<
	sge::sprite::buffers::single<
		sprite_choices
	>
> sprite_buffers_type;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

typedef sge::sprite::parameters<
	sprite_choices
> sprite_parameters;

typedef sge::sprite::state::all_choices sprite_state_choices;

typedef sge::sprite::state::object<
	sprite_state_choices
> sprite_state_object;

typedef sge::sprite::state::parameters<
	sprite_state_choices
> sprite_state_parameters;

typedef
fcppt::math::box::object<sge::renderer::scalar,2>
bvh_box;

typedef
sge::bvh::tree_traits
<
	sge::bvh::dummy_node,
	bvh_box,
	bvh_box
>
bvh_tree_traits;

typedef
sge::bvh::object<bvh_tree_traits>
bounding_hierarchy;

typedef
std::vector<sprite_object>
sprite_sequence;

static sprite_object const
create_sprite(
	bvh_box const &_rect,
	sge::image::color::rgba8 const &_color)
{
	return
		sprite_object(
				sprite_parameters()
					.pos(
						_rect.pos())
					.color(
							_color)
					.size(
						_rect.size()));
}

class bvh_traverser
{
FCPPT_NONCOPYABLE(
	bvh_traverser);
public:
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_VC_WARNING(4355)

	bvh_traverser(
		bvh_tree_traits::tree_representation const &_tree,
		sge::input::keyboard::device &_keyboard)
	:
		tree_(
			_tree),
		current_tree_(
			&tree_),
		keyboard_connection_(
			_keyboard.key_callback(
				std::tr1::bind(
					&bvh_traverser::keyboard_callback,
					this,
					std::tr1::placeholders::_1)))
	{
	}

	FCPPT_PP_POP_WARNING

	sprite_sequence const
	sprites() const
	{
		FCPPT_ASSERT_PRE(
			current_tree_);

		sprite_sequence result;

		// First, render the background
		result.push_back(
			create_sprite(
				current_tree_->value().get<bvh_tree_traits::node_wrapper>().bounding_box(),
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2e2621"),
					255)));

		if(fcppt::variant::holds_type<bvh_tree_traits::node_wrapper>(current_tree_->front().value()))
			result.push_back(
				create_sprite(
					current_tree_->front().value().get<bvh_tree_traits::node_wrapper>().bounding_box(),
					sge::image::color::rgba8_from_hex_string(
						std::string(
							"bee8e0"),
						255)));

		if(fcppt::variant::holds_type<bvh_tree_traits::node_wrapper>(current_tree_->back().value()))
			result.push_back(
				create_sprite(
					current_tree_->back().value().get<bvh_tree_traits::node_wrapper>().bounding_box(),
					sge::image::color::rgba8_from_hex_string(
						std::string(
							"ff5e00"),
						255)));

		// Then add the children
		this->add_children(
			result,
			current_tree_->front(),
			sge::image::color::rgba8_from_hex_string(
				std::string(
					"373c40"),
				204));

		// Then add the children
		this->add_children(
			result,
			current_tree_->back(),
			sge::image::color::rgba8_from_hex_string(
				std::string(
					"73320b"),
				204));

		return
			result;
	}
private:
	bvh_tree_traits::tree_representation const &tree_;
	bvh_tree_traits::tree_representation const *current_tree_;
	fcppt::signal::scoped_connection keyboard_connection_;

	void
	keyboard_callback(
		sge::input::keyboard::key_event const &_event)
	{
		FCPPT_ASSERT_PRE(
			current_tree_);

		if(!_event.pressed())
			return;

		bvh_tree_traits::tree_representation const *new_tree =
			0;

		switch(_event.key_code())
		{
			case sge::input::keyboard::key_code::left:
				new_tree = &(current_tree_->front());
				break;
			case sge::input::keyboard::key_code::right:
				new_tree = &(current_tree_->back());
				break;
			case sge::input::keyboard::key_code::up:
				new_tree = &(current_tree_->front());
				break;
			case sge::input::keyboard::key_code::down:
				new_tree = &(current_tree_->back());
				break;
			case sge::input::keyboard::key_code::p:
				if(current_tree_->has_parent())
					new_tree = &(current_tree_->parent());
				break;
			default:
				break;
		}

		if(!new_tree || new_tree->empty())
			return;

		current_tree_ =
			new_tree;
	}

	void
	add_children(
		sprite_sequence &_sprites,
		bvh_tree_traits::tree_representation const &_tree,
		sge::image::color::rgba8 const &_color) const
	{
		if(!_tree.empty())
		{
			for(
				bvh_tree_traits::tree_representation::child_list::const_iterator it =
					_tree.begin();
				it != _tree.end();
				++it)
				this->add_children(
					_sprites,
					*it,
					_color);
		}
		else
		{
			for(
				bvh_tree_traits::leaf_wrapper_sequence::const_iterator it =
					_tree.value().get<bvh_tree_traits::leaf_wrapper_sequence>().begin();
				it != _tree.value().get<bvh_tree_traits::leaf_wrapper_sequence>().end();
				++it)
				_sprites.push_back(
					create_sprite(
						it->value(),
						_color));
		}
	}
};
}


awl::main::exit_code const
example_main(
	awl::main::function_context const &_context
)
try
{
	if(_context.argc() == 1)
	{
		std::cerr << "Usage: " << _context.argv()[0] << " <rectangle-count>\n";
		return awl::main::exit_failure();
	}

	unsigned const rectangle_count =
		fcppt::extract_from_string_exn<unsigned>(
			std::string(
				_context.argv()[1]));

	sge::window::dim const window_dim(
		1024,
		1024
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("sge bvh example")
					),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::yes
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::center_on_resize(
					window_dim)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				),
				sge::systems::cursor_option_field()
			)
		)
	);


	sprite_buffers_type sprite_buffers(
		sys.renderer_ffp(),
		sge::sprite::buffers::option::dynamic
	);

	sprite_state_object sprite_state(
		sys.renderer_ffp(),
		sprite_state_parameters()
	);

	typedef
	fcppt::random::generator::minstd_rand
	generator_type;

	generator_type generator(
		fcppt::random::generator::seed_from_chrono<generator_type::seed>());

	typedef
	fcppt::random::distribution::uniform_real<sge::renderer::scalar>
	real_distribution;

	typedef
	fcppt::random::variate
	<
		generator_type,
		real_distribution
	>
	real_variate;

	/*
	typedef
	fcppt::random::distribution::uniform_int<unsigned>
	unsigned_distribution;

	typedef
	fcppt::random::variate
	<
		generator_type,
		unsigned_distribution
	>
	unsigned_variate;

	unsigned_variate
		object_count_rng(
			generator,
			unsigned_distribution(
				unsigned_distribution::min(
					5u),
				unsigned_distribution::max(
					50u)));
					*/

	real_variate
		screen_size_rng(
			generator,
			real_distribution(
				real_distribution::min(
					static_cast<sge::renderer::scalar>(window_dim.h())/8.0f),
				real_distribution::sup(
					static_cast<sge::renderer::scalar>(window_dim.h()) - static_cast<sge::renderer::scalar>(window_dim.h())/8.0f))),
		size_rng(
			generator,
			real_distribution(
				real_distribution::min(
					static_cast<sge::renderer::scalar>(window_dim.h())/16.0f),
				real_distribution::sup(
					static_cast<sge::renderer::scalar>(window_dim.h())/4.0f)));


	sge::bvh::object<bvh_tree_traits> bounding_hierarchy;

	bvh_tree_traits::leaf_sequence nodes;
	for(unsigned i = 0; i < rectangle_count; ++i)
	{
		bvh_box::dim const new_size(
			size_rng(),
			size_rng());

		nodes.push_back(
			bvh_box(
				bvh_box::vector(
					screen_size_rng(),
					screen_size_rng()) -
				new_size/2.0f,
				new_size));
	}

	{
		typedef
		boost::chrono::process_real_cpu_clock
		clock_type;

		clock_type::time_point const before =
			clock_type::now();

		bounding_hierarchy.insert(
			nodes);

		std::cout
			<< "Construction time: "
			<<
				boost::chrono::duration_cast<boost::chrono::milliseconds>(
					clock_type::now() - before).count()
			<< "\n";
	}

	std::cout << "Resulting tree depth: " << fcppt::container::tree::depth(bounding_hierarchy.representation()) << "\n";

	bvh_traverser traverser(
		bounding_hierarchy.representation(),
		sys.keyboard_collector());

	// Set running to false when escape is pressed.
	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	while(
		// Process window messages which will also process input.
		sys.window_system().poll()
	)
	{
		// Declare a render block, using the renderer's onscreen target.
		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		// Here, we clear the back buffer with the clear color black() on each frame.
		// We also clear the stencil buffer with value 0.
		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
		);

		// Render small sprite.
		sge::sprite::process::all(
			scoped_block.get(),
			sge::sprite::geometry::make_random_access_range(
				traverser.sprites()),
			sprite_buffers,
			sge::sprite::compare::default_(),
			sprite_state
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
