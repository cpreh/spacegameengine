//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/string.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/cg/program/from_string_parameters.hpp>
#include <sge/cg/program/main_function.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/source.hpp>
#include <sge/cg/program/source_type.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/cg/loaded_program.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/cg/scoped_program.hpp>
#include <sge/renderer/cg/scoped_texture.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_buffer_ref_container.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/create_buffer_from_vertices.hpp>
#include <sge/renderer/vertex/declaration.hpp>
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
#include <sge/systems/list.hpp>
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
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/make.hpp>
#include <fcppt/cast/dynamic.hpp>
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
          sge::systems::original_window(sge::window::title(FCPPT_TEXT("sge cg simple test"))))))(
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

  sge::cg::context::object const cg_context{};

  sge::cg::profile::object const vertex_profile(
      sys.renderer_device_core().create_cg_profile(sge::cg::profile::shader_type::vertex));

  sge::cg::string const vertex_shader_source("struct C2E1v_Output {\n"
                                             "	float4 position : POSITION;\n"
                                             "	float2 texCoord : TEXCOORD0;\n"
                                             "};\n"
                                             "\n"
                                             "C2E1v_Output\n"
                                             "C2E1v_tex(\n"
                                             "float2 position : POSITION,\n"
                                             "float2 texCoord : TEXCOORD0\n"
                                             ")\n"
                                             "{\n"
                                             "	C2E1v_Output OUT;\n"
                                             "\n"
                                             "	OUT.position = float4(position,0,1);\n"
                                             "	OUT.texCoord = texCoord;\n"
                                             "\n"
                                             "	return OUT;\n"
                                             "}\n");

  sge::cg::program::object vertex_program(sge::cg::program::from_string_parameters(
      cg_context,
      sge::cg::program::source_type::text,
      vertex_profile,
      sge::cg::program::source(vertex_shader_source),
      sge::cg::program::main_function("C2E1v_tex"),
      sys.renderer_device_core().cg_compile_options(cg_context, vertex_profile)));

  sge::renderer::cg::loaded_program_unique_ptr const loaded_vertex_program(
      sys.renderer_device_core().load_cg_program(fcppt::make_ref(vertex_program)));

  sge::cg::profile::object const pixel_profile(
      sys.renderer_device_core().create_cg_profile(sge::cg::profile::shader_type::pixel));

  sge::cg::string const pixel_shader_source(
      "// This is C3E3f_texture from \"The Cg Tutorial\" (Addison-Wesley, ISBN\n"
      "// 0321194969) by Randima Fernando and Mark J. Kilgard.  See page 67.\n"
      "\n"
      "struct C3E3f_Output {\n"
      "	float4 color : COLOR;\n"
      "};\n"
      "\n"
      "C3E3f_Output\n"
      "C3E3f_texture(\n"
      "	float2 texCoord : TEXCOORD0,\n"
      "	uniform sampler2D decal : TEX0\n"
      ")\n"
      "{\n"
      "	C3E3f_Output OUT;\n"
      "	OUT.color = tex2D(decal,texCoord);\n"
      "	return OUT;\n"
      "}\n");

  sge::cg::program::object pixel_program(sge::cg::program::from_string_parameters(
      cg_context,
      sge::cg::program::source_type::text,
      pixel_profile,
      sge::cg::program::source(pixel_shader_source),
      sge::cg::program::main_function("C3E3f_texture"),
      sys.renderer_device_core().cg_compile_options(cg_context, pixel_profile)));

  sge::renderer::cg::loaded_program_unique_ptr const loaded_pixel_program(
      sys.renderer_device_core().load_cg_program(fcppt::make_ref(pixel_program)));

  using pos3_type = sge::renderer::vf::pos<float, 3>;

  using texpos2_type = sge::renderer::vf::texpos<float, 2, sge::renderer::vf::index<0U>>;

  using format_part = sge::renderer::vf::part<pos3_type, texpos2_type>;

  using format = sge::renderer::vf::format<format_part>;

  sge::renderer::vertex::declaration_unique_ptr const vertex_declaration(
      sys.renderer_device_core().create_vertex_declaration(
          sge::renderer::vertex::declaration_parameters(
              sge::renderer::vf::dynamic::make_format<format>())));

  using pos3 = pos3_type::packed_type;

  using texpos2 = texpos2_type::packed_type;

  using vertex = sge::renderer::vf::vertex<format_part>;

  sge::renderer::vertex::buffer_unique_ptr const vertex_buffer(
      sge::renderer::vertex::create_buffer_from_vertices<format>(
          fcppt::make_ref(sys.renderer_device_core()),
          fcppt::make_cref(*vertex_declaration),
          sge::renderer::resource_flags_field::null(),
          fcppt::array::make(
              vertex{
                  sge::renderer::vf::labels::pos{} = pos3(-1.F, 1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = texpos2(0.F, 0.F)},
              vertex{
                  sge::renderer::vf::labels::pos{} = pos3(-1.F, -1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = texpos2(0.F, 1.F)},
              vertex{
                  sge::renderer::vf::labels::pos{} = pos3(1.F, 1.F, 0.F),
                  sge::renderer::vf::labels::texpos<0>{} = texpos2(1.F, 0.F)})));

  sge::renderer::texture::planar_unique_ptr const texture(
      sge::renderer::texture::create_planar_from_path(
          sge::config::media_path() / FCPPT_TEXT("images") / FCPPT_TEXT("uvtestgrid.png"),
          fcppt::make_ref(sys.renderer_device_core()),
          sys.image_system(),
          sge::renderer::texture::mipmap::off(),
          sge::renderer::resource_flags_field::null(),
          sge::renderer::texture::emulate_srgb_from_caps(sys.renderer_device_core().caps())));

  sge::renderer::cg::loaded_texture_unique_ptr const loaded_texture(
      sys.renderer_device_core().load_cg_texture(
          pixel_program.parameter("decal").object(),
          fcppt::reference_to_base<sge::renderer::texture::base>(fcppt::make_ref(*texture))));

  auto const draw(
      [&loaded_pixel_program,
       &loaded_texture,
       &loaded_vertex_program,
       &sys,
       &vertex_buffer,
       &vertex_declaration]
      {
        sge::renderer::context::scoped_core const scoped_block(
            fcppt::make_ref(sys.renderer_device_core()),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(sys.renderer_device_core().onscreen_target())));

        scoped_block.get().clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::blue()}));

        sge::renderer::vertex::scoped_declaration_and_buffers const vb_context(
            fcppt::make_ref(scoped_block.get()),
            fcppt::make_cref(*vertex_declaration),
            sge::renderer::vertex::const_buffer_ref_container{fcppt::make_cref(*vertex_buffer)});

        sge::renderer::cg::scoped_program const scoped_vertex_program(
            fcppt::make_ref(scoped_block.get()), fcppt::make_cref(*loaded_vertex_program));

        sge::renderer::cg::scoped_program const scoped_pixel_program(
            fcppt::make_ref(scoped_block.get()), fcppt::make_cref(*loaded_pixel_program));

        sge::renderer::cg::scoped_texture const scoped_texture(
            fcppt::make_ref(scoped_block.get()), fcppt::make_cref(*loaded_texture));

        scoped_block.get().render_nonindexed(
            sge::renderer::vertex::first(0U),
            sge::renderer::vertex::count(3U),
            sge::renderer::primitive_type::triangle_list);
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
