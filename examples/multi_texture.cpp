//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/create_buffer_from_indices.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_both.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_vertices.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/array/make.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
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
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input,
		sge::systems::with_image2d
	> const sys(
		sge::systems::make_list
		(
			sge::systems::config()
			.log_settings(
				sge::systems::log_settings(
					sge::log::option_container{
						sge::log::option{
							sge::log::location(),
							fcppt::log::level::debug
						}
					}
				)
			)
		)
		(
			sge::systems::window(
				sge::systems::window_source(
					sge::systems::original_window(
						sge::window::title(
							FCPPT_TEXT("sge multi texture sprite example")
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
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
	);

	sge::renderer::texture::planar_unique_ptr const texture1{
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("cloudsquare.png"),
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::yes
		)
	};

	sge::renderer::texture::planar_unique_ptr const texture2{
		sge::renderer::texture::create_planar_from_path(
			sge::config::media_path()
			/ FCPPT_TEXT("images")
			/ FCPPT_TEXT("grass.png"),
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			sys.image_system(),
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::emulate_srgb::yes
		)
	};

	typedef
	sge::renderer::vf::pos<
		float,
		3
	>
	vf_pos;

	typedef
	sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			0
		>
	>
	vf_texpos0;

	typedef
	sge::renderer::vf::texpos<
		float,
		2,
		sge::renderer::vf::index<
			1
		>
	>
	vf_texpos1;

	typedef
	sge::renderer::vf::part<
		vf_pos,
		vf_texpos0,
		vf_texpos1
	>
	vf_format_part;

	typedef
	sge::renderer::vf::format<
		vf_format_part
	>
	vf_format;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
		sys.renderer_device_ffp().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<
					vf_format
				>()
			)
		)
	);

	typedef
	sge::renderer::vf::vertex<
		vf_format_part
	>
	vertex;

	typedef
	vf_pos::packed_type pos;

	typedef
	vf_texpos0::packed_type texpos0;

	typedef
	vf_texpos1::packed_type texpos1;

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer{
		sge::renderer::vertex::create_buffer_from_vertices<
			vf_format
		>(
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			fcppt::make_cref(
				*vertex_declaration
			),
			sge::renderer::resource_flags_field::null(),
			fcppt::container::array::make(
				// top left
				vertex{
					sge::renderer::vf::labels::pos{} =
						pos(-1.f, 1.f, 0.f),
					sge::renderer::vf::labels::texpos<0>{} =
						texpos0(0.f, 0.f),
					sge::renderer::vf::labels::texpos<1>{} =
						texpos1(0.f, 0.f)
				},
				// bottom left
				vertex{
					sge::renderer::vf::labels::pos{} =
						pos(-1.f, -1.f, 0.f),
					sge::renderer::vf::labels::texpos<0>{} =
						texpos0(0.f, 1.f),
					sge::renderer::vf::labels::texpos<1>{} =
						texpos1(0.f, 1.f)
				},
				// top right
				vertex{
					sge::renderer::vf::labels::pos{} =
						pos(1.f, 1.f, 0.f),
					sge::renderer::vf::labels::texpos<0>{} =
						texpos0(1.f, 0.f),
					sge::renderer::vf::labels::texpos<1>{} =
						texpos1(1.f, 0.f)
				},
				// bottom right
				vertex{
					sge::renderer::vf::labels::pos{} =
						pos(1.f, -1.f, 0.f),
					sge::renderer::vf::labels::texpos<0>{} =
						texpos0(1.f, 1.f),
					sge::renderer::vf::labels::texpos<1>{} =
						texpos1(1.f, 1.f)
				}
			)
		)
	};

	typedef
	sge::renderer::index::i16
	i16;

	sge::renderer::index::buffer_unique_ptr const index_buffer{
		sge::renderer::index::create_buffer_from_indices(
			fcppt::make_ref(
				sys.renderer_device_core()
			),
			sge::renderer::resource_flags_field::null(),
			fcppt::container::array::make(
				fcppt::literal<i16>(0),
				fcppt::literal<i16>(1),
				fcppt::literal<i16>(2),
				fcppt::literal<i16>(2),
				fcppt::literal<i16>(3),
				fcppt::literal<i16>(1)
			)
		)
	};

	sge::renderer::state::ffp::sampler::object_unique_ptr const sampler0{
		sys.renderer_device_ffp().create_ffp_sampler_state(
			sge::renderer::state::ffp::sampler::parameters_both(
				sge::renderer::state::ffp::sampler::op(
					sge::renderer::state::ffp::sampler::unary_op(
						sge::renderer::state::ffp::sampler::unary_op_type::arg,
						sge::renderer::state::ffp::sampler::arg1(
							sge::renderer::state::ffp::sampler::arg::texture
						)
					)
				)
			)
		)
	};

	sge::renderer::state::ffp::sampler::object_unique_ptr const sampler1{
		sys.renderer_device_ffp().create_ffp_sampler_state(
			sge::renderer::state::ffp::sampler::parameters_both(
				sge::renderer::state::ffp::sampler::op(
					sge::renderer::state::ffp::sampler::binary_op(
						sge::renderer::state::ffp::sampler::binary_op_type::modulate,
						sge::renderer::state::ffp::sampler::arg1(
							sge::renderer::state::ffp::sampler::arg::previous
						),
						sge::renderer::state::ffp::sampler::arg2(
							sge::renderer::state::ffp::sampler::arg::texture
						)
					)
				)
			)
		)
	};

	sge::renderer::state::ffp::sampler::const_object_ref_vector const samplers{
		fcppt::make_cref(
			*sampler0
		),
		fcppt::make_cref(
			*sampler1
		)
	};

	auto const draw(
		[
			&index_buffer,
			&samplers,
			&sys,
			&texture1,
			&texture2,
			&vertex_buffer,
			&vertex_declaration
		]{
			sge::renderer::context::scoped_ffp const scoped_block(
				fcppt::make_ref(
					sys.renderer_device_ffp()
				),
				fcppt::reference_to_base<
					sge::renderer::target::base
				>(
					fcppt::make_ref(
						sys.renderer_device_ffp().onscreen_target()
					)
				)
			);

			sge::renderer::vertex::scoped_declaration const vb_declaration_context(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						scoped_block.get()
					)
				),
				fcppt::make_cref(
					*vertex_declaration
				)
			);

			sge::renderer::vertex::scoped_buffer const vb_context(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						scoped_block.get()
					)
				),
				fcppt::make_cref(
					*vertex_buffer
				)
			);

			sge::renderer::texture::scoped const tex0_context(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						scoped_block.get()
					)
				),
				fcppt::reference_to_base<
					sge::renderer::texture::base const
				>(
					fcppt::make_cref(
						*texture1
					)
				),
				sge::renderer::texture::stage(0u)
			);

			sge::renderer::texture::scoped const tex1_context(
				fcppt::reference_to_base<
					sge::renderer::context::core
				>(
					fcppt::make_ref(
						scoped_block.get()
					)
				),
				fcppt::reference_to_base<
					sge::renderer::texture::base const
				>(
					fcppt::make_cref(
						*texture2
					)
				),
				sge::renderer::texture::stage(1u)
			);

			scoped_block.get().sampler_ffp_state(
				samplers
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			scoped_block.get().render_indexed(
				*index_buffer,
				sge::renderer::vertex::first(
					0u
				),
				sge::renderer::vertex::count(
					vertex_buffer->linear_size()
				),
				sge::renderer::primitive_type::triangle_list,
				sge::renderer::index::first(
					0u
				),
				sge::renderer::index::count(
					index_buffer->linear_size()
				)
			);
		}
	);

	return
		sge::window::loop(
			sys.window_system(),
			sge::window::loop_function{
				[
					&sys,
					&draw
				](
					awl::event::base const &_event
				)
				{
					sge::systems::quit_on_escape(
						sys,
						_event
					);

					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
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
