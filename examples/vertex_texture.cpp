//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/media_path.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/index/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/create_buffer_from_indices.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/scoped.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/buffer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_vertices.hpp>
#include <sge/renderer/vertex/declaration.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_declaration_and_buffers.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
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
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/make.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/math/vector/static.hpp> // IWYU pragma: keep
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>

awl::main::exit_code example_main(awl::main::function_context const &)
try
{
  sge::systems::instance<
      sge::systems::with_window,
      sge::systems::with_renderer<sge::systems::renderer_caps::core>,
      sge::systems::with_input,
      sge::systems::with_image2d> const
      sys(sge::systems::make_list(sge::systems::window(sge::systems::window_source(
          sge::systems::original_window(sge::window::title(FCPPT_TEXT("sge vertex example"))))))(
          sge::systems::renderer(
              sge::renderer::pixel_format::object(
                  sge::renderer::pixel_format::color::depth32,
                  sge::renderer::pixel_format::depth_stencil::off,
                  sge::renderer::pixel_format::optional_multi_samples(),
                  sge::renderer::pixel_format::srgb::no),
              sge::renderer::display_mode::parameters(
                  sge::renderer::display_mode::vsync::on,
                  sge::renderer::display_mode::optional_object()),
              sge::viewport::optional_resize_callback{sge::viewport::fill_on_resize()}))(
          sge::systems::image2d(sge::media::optional_extension_set(
              sge::media::extension_set{sge::media::extension(FCPPT_TEXT("png"))})))(
          sge::systems::input(sge::systems::cursor_option_field::null())));

  using pos3_type = sge::renderer::vf::pos<float, 3>;

  using texpos2_type = sge::renderer::vf::texpos<float, 2, sge::renderer::vf::index<0U>>;

  using format_part = sge::renderer::vf::part<pos3_type, texpos2_type>;

  using format = sge::renderer::vf::format<format_part>;

  sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
      sys.renderer_device_core().create_vertex_declaration(
          sge::renderer::vertex::declaration_parameters(
              sge::renderer::vf::dynamic::make_format<format>())));

  using vertex = sge::renderer::vf::vertex<format_part>;

  using vec3 = pos3_type::packed_type;

  using vec2 = texpos2_type::packed_type;

  sge::renderer::vertex::buffer_unique_ptr const vertex_buffer{
      sge::renderer::vertex::create_buffer_from_vertices<format>(
          fcppt::make_ref(sys.renderer_device_core()),
          fcppt::make_cref(*vertex_declaration),
          sge::renderer::resource_flags_field::null(),
          fcppt::array::make(
              vertex{
                  sge::renderer::vf::labels::pos{} = vec3(-1.F, 1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = vec2(0.F, 0.F)},
              vertex{
                  sge::renderer::vf::labels::pos{} = vec3(-1.F, -1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = vec2(0.F, 1.F)},
              vertex{
                  sge::renderer::vf::labels::pos{} = vec3(1.F, 1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = vec2(1.F, 0.F)},
              vertex{
                  sge::renderer::vf::labels::pos{} = vec3(1.F, -1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = vec2(1.F, 1.F)}))};

  using i16 = sge::renderer::index::i16;

  sge::renderer::index::buffer_unique_ptr const index_buffer{
      sge::renderer::index::create_buffer_from_indices(
          fcppt::make_ref(sys.renderer_device_core()),
          sge::renderer::resource_flags_field::null(),
          fcppt::array::make(
              fcppt::literal<i16>(0),
              fcppt::literal<i16>(1),
              fcppt::literal<i16>(2),
              fcppt::literal<i16>(1),
              fcppt::literal<i16>(3),
              fcppt::literal<i16>(2)))};

  sge::renderer::texture::planar_unique_ptr const texture(
      sge::renderer::texture::create_planar_from_path(
          sge::config::media_path() / FCPPT_TEXT("images") / FCPPT_TEXT("grass.png"),
          fcppt::make_ref(sys.renderer_device_core()),
          sys.image_system(),
          sge::renderer::texture::mipmap::off(),
          sge::renderer::resource_flags_field::null(),
          sge::renderer::texture::emulate_srgb_from_caps(sys.renderer_device_core().caps())));

  auto const draw(
      [&index_buffer, &sys, &texture, &vertex_buffer, &vertex_declaration]
      {
        sge::renderer::context::scoped_core const scoped_block(
            fcppt::make_ref(sys.renderer_device_core()),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(sys.renderer_device_core().onscreen_target())));

        sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
            fcppt::make_ref(scoped_block.get()),
            fcppt::make_cref(*vertex_declaration),
            sge::renderer::vertex::const_buffer_ref_container{fcppt::make_cref(*vertex_buffer)});

        sge::renderer::texture::scoped const tex_context(
            fcppt::make_ref(scoped_block.get()),
            fcppt::reference_to_base<sge::renderer::texture::base const>(
                fcppt::make_cref(*texture)),
            sge::renderer::texture::stage(0U));

        scoped_block.get().render_indexed(
            *index_buffer,
            sge::renderer::vertex::first(0U),
            sge::renderer::vertex::count(
                4U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                ),
            sge::renderer::primitive_type::triangle_list,
            sge::renderer::index::first(0U),
            sge::renderer::index::count(
                6U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                ));
      });

  return sge::window::loop(
      sys.window_system(),
      sge::window::loop_function{
          [&sys, &draw](awl::event::base const &_event)
          {
            sge::systems::quit_on_escape(sys, _event);

            fcppt::optional::maybe_void(
                fcppt::cast::dynamic<sge::renderer::event::render const>(_event),
                [&draw](fcppt::reference<sge::renderer::event::render const>) { draw(); });
          }});
}
catch (fcppt::exception const &_error)
{
  awl::show_error(_error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(_error.what());

  return awl::main::exit_failure();
}
