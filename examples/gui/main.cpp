/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/config/media_path.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/system.hpp>
#include <sge/gui/click_callback.hpp>
#include <sge/gui/context.hpp>
#include <sge/gui/create_texture.hpp>
#include <sge/gui/duration.hpp>
#include <sge/gui/index.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/optional_index.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/string_container.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/style/base.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>
#include <sge/gui/style/create.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/choices.hpp>
#include <sge/gui/widget/edit.hpp>
#include <sge/gui/widget/image.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/gui/widget/reference_name_vector.hpp>
#include <sge/gui/widget/reference_tree.hpp>
#include <sge/gui/widget/reference_tree_vector.hpp>
#include <sge/gui/widget/tab.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/gui/widget/tree.hpp>
#include <sge/gui/widget/tree_unique_ptr.hpp>
#include <sge/gui/widget/unique_ptr.hpp>
#include <sge/gui/widget/unique_ptr_tree.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/input/event_base.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <sge/timer/basic.hpp>
#include <sge/timer/elapsed_and_reset.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/timer/clocks/standard.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/container/tree/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <chrono>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


awl::main::exit_code const
example_main(
	awl::main::function_context const &
)
try
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_font,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_window,
			sge::systems::with_input,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("gui test")
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
					sge::viewport::fill_on_resize()
				}
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
	);

	sge::font::object_unique_ptr const font(
		sys.font_system().create_font(
			sge::font::parameters()
			.dpi(
				sge::renderer::display_mode::to_dpi(
					sys.renderer_device_ffp().display_mode()
				)
			)
		)
	);

	sge::gui::style::base_unique_ptr const style{
		sge::gui::style::create()
	};

	sge::gui::context context;

	sge::gui::widget::button button(
		*style,
		sys.renderer_device_ffp(),
		*font,
		SGE_FONT_LIT("Quit"),
		sge::gui::optional_needed_width()
	);

	fcppt::signal::auto_connection const quit_connection(
		button.click(
			sge::gui::click_callback{
				[
					&sys
				]()
				{
					sys.window_system().quit(
						awl::main::exit_success()
					);
				}
			}
		)
	);

	sge::gui::widget::edit edit(
		*style,
		sys.renderer_device_ffp(),
		*font,
		SGE_FONT_LIT("Test")
	);

	sge::texture::part_raw_ptr const car_image(
		sge::gui::create_texture(
			sys.renderer_device_core(),
			sge::image2d::load_exn(
				sys.image_system(),
				sge::config::media_path()
				/
				FCPPT_TEXT("images")
				/
				FCPPT_TEXT("tux.png")
			)->view()
		)
	);

	sge::gui::widget::image image(
		*style,
		car_image
	);

	auto const make_tree(
		[
			&style,
			&sys,
			&font
		](
			sge::font::string const &_label
		)
		{
			return
				sge::gui::widget::unique_ptr_tree(
					fcppt::unique_ptr_to_base<
						sge::gui::widget::base
					>(
						fcppt::make_unique_ptr<
							sge::gui::widget::text
						>(
							*style,
							sys.renderer_device_ffp(),
							*font,
							_label,
							sge::gui::text_color(
								sge::image::color::any::object{
									sge::image::color::predef::black()
								}
							),
							sge::gui::optional_needed_width()
						)
					),
					fcppt::assign::make_container<
						sge::gui::widget::unique_ptr_tree::child_list
					>(
						sge::gui::widget::unique_ptr_tree(
							fcppt::unique_ptr_to_base<
								sge::gui::widget::base
							>(
								fcppt::make_unique_ptr<
									sge::gui::widget::button
								>(
									*style,
									sys.renderer_device_ffp(),
									*font,
									SGE_FONT_LIT("Child 1"),
									sge::gui::optional_needed_width()
								)
							)
						),
						sge::gui::widget::unique_ptr_tree(
							fcppt::unique_ptr_to_base<
								sge::gui::widget::base
							>(
								fcppt::make_unique_ptr<
									sge::gui::widget::button
								>(
									*style,
									sys.renderer_device_ffp(),
									*font,
									SGE_FONT_LIT("Child 2 asdljasdljasdklasdjklasdjlkasdjaskldjjasdkljasdklasdjlk"),
									sge::gui::optional_needed_width()
								)
							)
						)
					)
				);
		}
	);

	auto const make_widget_tree(
		[
			&context
		](
			sge::gui::widget::unique_ptr_tree const &_tree
		)
		{
			return
				fcppt::make_unique_ptr<
					sge::gui::widget::tree
				>(
					context,
					sge::gui::widget::reference_tree_vector{
						fcppt::container::tree::map<
							sge::gui::widget::reference_tree
						>(
							_tree,
							[](
								sge::gui::widget::unique_ptr const &_widget
							)
							{
								return
									sge::gui::widget::reference(
										*_widget
									);
							}
						)
					}
				);
		}
	);

	sge::gui::widget::unique_ptr_tree tree1_widgets(
		make_tree(
			SGE_FONT_LIT("Toplevel 1")
		)
	);

	sge::gui::widget::tree_unique_ptr tree1(
		make_widget_tree(
			tree1_widgets
		)
	);

	sge::gui::widget::unique_ptr_tree tree2_widgets(
		make_tree(
			SGE_FONT_LIT("Toplevel 2")
		)
	);

	sge::gui::widget::tree_unique_ptr tree2(
		make_widget_tree(
			tree2_widgets
		)
	);

	sge::gui::widget::tab tab(
		context,
		*style,
		sys.renderer_device_ffp(),
		*font,
		sge::gui::widget::reference_name_vector{
			sge::gui::widget::reference_name_pair(
				sge::gui::widget::reference(
					*tree1
				),
				SGE_FONT_LIT("Tab 1 asdkljasdlasdlkasdjklasdjklasdjklasjjklasdfoasdioasdjhiosjjaojasdfojasdfojasdfoasdfjaklasdgjkl")
			),
			sge::gui::widget::reference_name_pair(
				sge::gui::widget::reference(
					*tree2
				),
				SGE_FONT_LIT("Tab 2")
			)
		}
	);

	sge::gui::widget::box_container line_widget(
		context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					button
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					edit
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					image
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x
	);

	sge::gui::string_container const string_choices{
		SGE_FONT_LIT("Choices Short"),
		SGE_FONT_LIT("Choices Loooooooooooooooooooooooooooooooooooong")
	};

	sge::gui::widget::choices choices(
		context,
		*style,
		sys.renderer_device_ffp(),
		*font,
		string_choices,
		sge::gui::optional_index(
			sge::gui::index(
				0u
			)
		)
	);

	sge::gui::widget::box_container main_widget(
		context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					tab
				),
				sge::rucksack::alignment::left_or_top
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					line_widget
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					choices
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::y
	);

	sge::gui::main_area::viewport_adaptor main_area(
		sys.renderer_device_ffp(),
		sys.viewport_manager(),
		main_widget
	);

	sge::gui::master master(
		context,
		main_area
	);

	sge::gui::background::colored background(
		main_area
	);

	typedef
	sge::timer::basic<
		sge::timer::clocks::standard
	>
	frame_timer_type;

	frame_timer_type frame_timer(
		frame_timer_type::parameters(
			std::chrono::seconds(
				1
			)
		)
	);

	auto const draw(
		[
			&background,
			&frame_timer,
			&master,
			&sys
		]{
			sge::timer::scoped_frame_limiter const limiter(
				sge::renderer::display_mode::desired_fps(
					sys.renderer_device_ffp().display_mode()
				)
			);

			master.update(
				std::chrono::duration_cast<
					sge::gui::duration
				>(
					sge::timer::elapsed_and_reset(
						frame_timer
					)
				)
			);

			sge::renderer::context::scoped_ffp const scoped_block(
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::blue()
					}
				)
			);

			master.draw_with_states(
				sys.renderer_device_ffp(),
				scoped_block.get(),
				background
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&master,
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							brigand::list<
								sge::renderer::event::render const,
								sge::input::event_base const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							&master,
							&draw
						](
							auto const &_variant
						)
						{
							fcppt::variant::match(
								_variant,
								[
									&draw
								](
									fcppt::reference<
										sge::renderer::event::render const
									>
								)
								{
									draw();
								},
								[
									&master
								](
									fcppt::reference<
										sge::input::event_base const
									> const _input_event
								)
								{
									master.process_event(
										_input_event.get()
									);
								}
							);
						}
					);
				}
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}
