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
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/scoped_lock.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
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
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
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
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
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
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input,
			sge::systems::with_image2d
		>
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
			sys.renderer_device_ffp(),
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
			sys.renderer_device_ffp(),
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
		brigand::list<
			vf_pos,
			vf_texpos0,
			vf_texpos1
		>
	>
	vf_format_part;

	typedef
	sge::renderer::vf::format<
		brigand::list<
			vf_format_part
		>
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

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
		sys.renderer_device_ffp().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration,
				sge::renderer::vf::dynamic::make_part_index<
					vf_format,
					vf_format_part
				>(),
				sge::renderer::vertex::count(
					4u
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	{
		sge::renderer::vertex::scoped_lock const vblock(
			*vertex_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef
		sge::renderer::vf::view<
			vf_format_part
		>
		vertex_view;

		vertex_view const vertices(
			vblock.value()
		);

		vertex_view::iterator vb_it(
			vertices.begin()
		);

		typedef
		vf_pos::packed_type pos;

		typedef
		vf_texpos0::packed_type texpos0;

		typedef
		vf_texpos1::packed_type texpos1;

		// top left
		(*vb_it).set<
			vf_pos
		>(
			pos(-1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(0.f, 0.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(0.f, 0.f)
		);

		// bottom left
		(*vb_it).set<
			vf_pos
		>(
			pos(-1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(0.f, 1.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(0.f, 1.f)
		);

		// top right
		(*vb_it).set<
			vf_pos
		>(
			pos(1.f, 1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(1.f, 0.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(1.f, 0.f)
		);

		// bottom right
		(*vb_it).set<
			vf_pos
		>(
			pos(1.f, -1.f, 0.f)
		);

		(*vb_it).set<
			vf_texpos0
		>(
			texpos0(1.f, 1.f)
		);

		(*vb_it++).set<
			vf_texpos1
		>(
			texpos1(1.f, 1.f)
		);
	}

	typedef
	sge::renderer::index::format_16
	index_format;

	sge::renderer::index::buffer_unique_ptr const index_buffer(
		sys.renderer_device_ffp().create_index_buffer(
			sge::renderer::index::buffer_parameters(
				sge::renderer::index::dynamic::make_format<
					index_format
				>(),
				sge::renderer::index::count(
					6u
				),
				sge::renderer::resource_flags_field::null()
			)
		)
	);

	{
		sge::renderer::index::scoped_lock const iblock(
			*index_buffer,
			sge::renderer::lock_mode::writeonly
		);

		typedef
		sge::renderer::index::view<
			index_format
		>
		index_view;

		index_view const indices(
			iblock.value()
		);

		typedef
		index_view::iterator
		index_iterator;

		index_iterator ib_it{
			indices.begin()
		};

		(*ib_it++).set(0);
		(*ib_it++).set(1);
		(*ib_it++).set(2);
		(*ib_it++).set(2);
		(*ib_it++).set(3);
		(*ib_it++).set(1);
	}

	fcppt::signal::auto_connection const escape_connection{
		sge::systems::quit_on_escape(
			sys
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
				sys.renderer_device_ffp(),
				sys.renderer_device_ffp().onscreen_target()
			);

			sge::renderer::vertex::scoped_declaration const vb_declaration_context(
				scoped_block.get(),
				*vertex_declaration
			);

			sge::renderer::vertex::scoped_buffer const vb_context(
				scoped_block.get(),
				*vertex_buffer
			);

			sge::renderer::texture::scoped const tex0_context(
				scoped_block.get(),
				*texture1,
				sge::renderer::texture::stage(0u)
			);

			sge::renderer::texture::scoped const tex1_context(
				scoped_block.get(),
				*texture2,
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
					&draw
				](
					awl::event::base const &_event
				)
				{
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
