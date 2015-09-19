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


#include <sge/bvh/dummy_node.hpp>
#include <sge/bvh/object_impl.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8_from_hex_string.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/default.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/container/tree/depth.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/get_exn.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <example_main.hpp>
#include <exception>
#include <functional>
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
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::never
	>,
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

sprite_object const
create_sprite(
	bvh_box const &_rect,
	sge::image::color::rgba8 const &_color)
{
	return
		sprite_object(
			sge::sprite::roles::pos{} =
				_rect.pos(),
			sge::sprite::roles::color{} =
				_color,
			sge::sprite::roles::size{} =
				_rect.size()
		);
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
			tree_),
		keyboard_connection_(
			_keyboard.key_callback(
				sge::input::keyboard::key_callback{
					std::bind(
						&bvh_traverser::keyboard_callback,
						this,
						std::placeholders::_1
					)
				}
			)
		)
	{
	}

	FCPPT_PP_POP_WARNING

	sprite_sequence const
	sprites() const
	{
		bvh_tree_traits::tree_representation const &tree(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				current_tree_
			)
		);

		sprite_sequence result;

		// First, render the background
		result.push_back(
			create_sprite(
				fcppt::variant::get_exn<
					bvh_tree_traits::node_wrapper
				>(
					tree.value()
				).bounding_box(),
				sge::image::color::rgba8_from_hex_string(
					std::string(
						"2e2621"),
					255)));

		fcppt::maybe_void(
			fcppt::variant::to_optional<
				bvh_tree_traits::node_wrapper
			>(
				tree.front().value()
			),
			[
				&result
			](
				bvh_tree_traits::node_wrapper const &_wrapper
			)
			{
				result.push_back(
					create_sprite(
						_wrapper.bounding_box(),
						sge::image::color::rgba8_from_hex_string(
							std::string(
								"bee8e0"
							),
							255
						)
					)
				);
			}
		);

		fcppt::maybe_void(
			fcppt::variant::to_optional<
				bvh_tree_traits::node_wrapper
			>(
				tree.back().value()
			),
			[
				&result
			](
				bvh_tree_traits::node_wrapper const &_wrapper
			)
			{
				result.push_back(
					create_sprite(
						_wrapper.bounding_box(),
						sge::image::color::rgba8_from_hex_string(
							std::string(
								"ff5e00"
							),
							255
						)
					)
				);
			}
		);

		// Then add the children
		this->add_children(
			result,
			tree.front(),
			sge::image::color::rgba8_from_hex_string(
				std::string(
					"373c40"),
				204));

		// Then add the children
		this->add_children(
			result,
			tree.back(),
			sge::image::color::rgba8_from_hex_string(
				std::string(
					"73320b"),
				204));

		return
			result;
	}
private:
	bvh_tree_traits::tree_representation const &tree_;
	bvh_tree_traits::tree_representation::const_optional_ref current_tree_;
	fcppt::signal::auto_connection keyboard_connection_;

	void
	keyboard_callback(
		sge::input::keyboard::key_event const &_event)
	{
		bvh_tree_traits::tree_representation const &tree(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				current_tree_
			)
		);

		if(!_event.pressed())
			return;

		bvh_tree_traits::tree_representation::const_optional_ref new_tree;

		switch(_event.key().code())
		{
			case sge::input::key::code::left:
				new_tree =
					bvh_tree_traits::tree_representation::const_optional_ref(
						tree.front());
				break;
			case sge::input::key::code::right:
				new_tree =
					bvh_tree_traits::tree_representation::const_optional_ref(
						 tree.back());
				break;
			case sge::input::key::code::up:
				new_tree =
					bvh_tree_traits::tree_representation::const_optional_ref(
						tree.front());
				break;
			case sge::input::key::code::down:
				new_tree =
					bvh_tree_traits::tree_representation::const_optional_ref(
						tree.back());
				break;
			case sge::input::key::code::p:
				fcppt::maybe_void(
					tree.parent(),
					[
						&new_tree
					](
						bvh_tree_traits::tree_representation const &_parent
					)
					{
						new_tree =
							bvh_tree_traits::tree_representation::const_optional_ref(
								_parent
							);
					}
				);
				break;
			default:
				break;
		}

		if(
			fcppt::maybe(
				new_tree,
				fcppt::const_(
					true
				),
				[](
					bvh_tree_traits::tree_representation const &_new_tree
				)
				{
					return
						_new_tree.empty();
				}
			)
		)
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
				auto const &child : _tree
			)
				this->add_children(
					_sprites,
					child,
					_color);
		}
		else
		{
			for(
				auto const &elem
				:
				fcppt::variant::get_exn<
					bvh_tree_traits::leaf_wrapper_sequence
				>(
					_tree.value()
				)
			)
				_sprites.push_back(
					create_sprite(
						elem.value(),
						_color
					)
				);
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

	// TODO: Remove this
	sge::window::dim const window_dim(
		1024u,
		1024u
	);

	sge::systems::instance<
		boost::mpl::vector3<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector1<
					sge::systems::keyboard_collector
				>
			>
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge bvh example")
						)
					)
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::optional_resize_callback{
					sge::viewport::center_on_resize(
						window_dim
					)
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);


	sprite_buffers_type sprite_buffers(
		sys.renderer_device_ffp(),
		sge::sprite::buffers::option::dynamic
	);

	sprite_state_object sprite_state(
		sys.renderer_device_ffp(),
		sprite_state_parameters()
	);

	typedef
	fcppt::random::generator::minstd_rand
	generator_type;

	generator_type generator(
		fcppt::random::generator::seed_from_chrono<generator_type::seed>());

	typedef
	fcppt::random::distribution::basic
	<
		fcppt::random::distribution::parameters::uniform_real
		<
			sge::renderer::scalar
		>
	>
	real_distribution;

	typedef
	fcppt::random::variate
	<
		generator_type,
		real_distribution
	>
	real_variate;

	real_variate
		screen_size_rng(
			generator,
			real_distribution(
				real_distribution::param_type::min(
					fcppt::cast::int_to_float<
						sge::renderer::scalar
					>(
						window_dim.h()
					)
					/
					fcppt::literal<
						sge::renderer::scalar
					>(
						8
					)
				),
				real_distribution::param_type::sup(
					fcppt::cast::int_to_float<
						sge::renderer::scalar
					>(
						window_dim.h()
					)
					-
					fcppt::cast::int_to_float<
						sge::renderer::scalar
					>(
						window_dim.h()
					)
					/
					fcppt::literal<
						sge::renderer::scalar
					>(
						8
					)
				)
			)
		),
		size_rng(
			generator,
			real_distribution(
				real_distribution::param_type::min(
					fcppt::cast::int_to_float<
						sge::renderer::scalar
					>(
						window_dim.h()
					)
					/
					fcppt::literal<
						sge::renderer::scalar
					>(
						16
					)
				),
				real_distribution::param_type::sup(
					fcppt::cast::int_to_float<
						sge::renderer::scalar
					>(
						window_dim.h()
					)
					/
					fcppt::literal<
						sge::renderer::scalar
					>(
						4
					)
				)
			)
		);


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
		std::chrono::steady_clock
		clock_type;

		clock_type::time_point const before =
			clock_type::now();

		bounding_hierarchy.insert(
			nodes);

		std::cout
			<< "Construction time: "
			<<
				std::chrono::duration_cast<std::chrono::milliseconds>(
					clock_type::now() - before).count()
			<< "\n";
	}

	std::cout << "Resulting tree depth: " << fcppt::container::tree::depth(bounding_hierarchy.representation()) << "\n";

	bvh_traverser traverser(
		bounding_hierarchy.representation(),
		sys.keyboard_collector());

	// Set running to false when escape is pressed.
	fcppt::signal::auto_connection const escape_connection(
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
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		// Here, we clear the back buffer with the clear color black() on each frame.
		// We also clear the stencil buffer with value 0.
		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::color::predef::black()
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
