//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/media_path.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/state/core/blend/object.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/default.hpp>
#include <sge/renderer/state/core/sampler/filter/mipmap.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/render_context/cg/light/directional.hpp>
#include <sge/scenic/render_context/cg/light/point.hpp>
#include <sge/shader/context.hpp>
#include <sge/shader/context_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/math/matrix/identity.hpp>
#include <fcppt/math/vector/null.hpp>

sge::scenic::render_context::cg::manager::manager(
    sge::shader::context_ref const _shader_context,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration)
    : sge::scenic::render_context::manager_base(),
      vertex_declaration_{_vertex_declaration},
      shader_(
          _shader_context,
          _vertex_declaration.get(),
          sge::shader::vertex_program_path(
              sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
          sge::shader::pixel_program_path(
              sge::config::media_path() / FCPPT_TEXT("shaders") / FCPPT_TEXT("ffp.cg")),
          sge::shader::optional_cflags(sge::shader::optional_cflags::string_sequence{
              "-DMAX_POINT_LIGHTS=" + fcppt::output_to_std_string(max_point_lights::value),
              "-DMAX_DIRECTIONAL_LIGHTS=" +
                  fcppt::output_to_std_string(max_directional_lights::value)})),
      world_matrix_(
          fcppt::make_ref(shader_.vertex_program()),
          sge::shader::parameter::name("camera.world"),
          _shader_context.get().renderer(),
          sge::shader::parameter::is_projection_matrix(false),
          fcppt::math::matrix::identity<sge::renderer::matrix4>()),
      world_projection_matrix_(
          fcppt::make_ref(shader_.vertex_program()),
          sge::shader::parameter::name("camera.world_projection"),
          _shader_context.get().renderer(),
          sge::shader::parameter::is_projection_matrix(true),
          fcppt::math::matrix::identity<sge::renderer::matrix4>()),
      world_inverse_transpose_matrix_(
          fcppt::make_ref(shader_.vertex_program()),
          sge::shader::parameter::name("camera.world_it"),
          _shader_context.get().renderer(),
          sge::shader::parameter::is_projection_matrix(false),
          fcppt::math::matrix::identity<sge::renderer::matrix4>()),
      material_diffuse_color_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("current_material.diffuse_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      material_specular_color_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("current_material.specular_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      material_ambient_color_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("current_material.ambient_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      material_emissive_color_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("current_material.emissive_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      material_shininess_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("current_material.shininess"),
          sge::renderer::scalar()),
      use_diffuse_texture_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("use_diffuse_texture"),
          false),
      diffuse_texture_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("diffuse_texture"),
          fcppt::make_ref(shader_),
          fcppt::make_ref(shader_.context().renderer()),
          sge::shader::parameter::planar_texture::optional_value()),
      use_specular_texture_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("use_specular_texture"),
          false),
      specular_texture_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("specular_texture"),
          fcppt::make_ref(shader_),
          fcppt::make_ref(shader_.context().renderer()),
          sge::shader::parameter::planar_texture::optional_value()),
      point_light_count_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("point_light_count"),
          0),
      directional_light_count_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("directional_light_count"),
          0),
      use_fog_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("fog_information.enabled"),
          false),
      fog_start_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("fog_information.start"),
          sge::renderer::scalar()),
      fog_end_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("fog_information.end"),
          sge::renderer::scalar()),
      fog_color_(
          fcppt::make_ref(shader_.pixel_program()),
          sge::shader::parameter::name("fog_information.color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      point_lights_(fcppt::array::init<point_light_array>(
          [this](auto const _index)
          {
            return fcppt::make_unique_ptr<sge::scenic::render_context::cg::light::point>(
                fcppt::make_ref(shader_.pixel_program()),
                sge::scenic::render_context::cg::light::index(_index));
          })),
      directional_lights_(fcppt::array::init<directional_light_array>(
          [this](auto const _index)
          {
            return fcppt::make_unique_ptr<sge::scenic::render_context::cg::light::directional>(
                fcppt::make_ref(shader_.pixel_program()),
                sge::scenic::render_context::cg::light::index(_index));
          })),
      depth_stencil_state_(_shader_context.get().renderer().create_depth_stencil_state(
          sge::renderer::state::core::depth_stencil::parameters(
              sge::renderer::state::core::depth_stencil::depth::variant(
                  sge::renderer::state::core::depth_stencil::depth::enabled(
                      sge::renderer::state::core::depth_stencil::depth::func::less,
                      sge::renderer::state::core::depth_stencil::depth::write_enable(true))),
              sge::renderer::state::core::depth_stencil::stencil::variant(
                  sge::renderer::state::core::depth_stencil::stencil::off())))),
      blend_state_(_shader_context.get().renderer().create_blend_state(
          sge::renderer::state::core::blend::parameters(
              sge::renderer::state::core::blend::alpha_variant(
                  sge::renderer::state::core::blend::alpha_off()),
              sge::renderer::state::core::blend::write_mask_all()))),
      rasterizer_state_(_shader_context.get().renderer().create_rasterizer_state(
          sge::renderer::state::core::rasterizer::parameters(
              sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise,
              sge::renderer::state::core::rasterizer::fill_mode::solid,
              sge::renderer::state::core::rasterizer::enable_scissor_test(false)))),
      mipmap_sampler_state_(_shader_context.get().renderer().create_sampler_state(
          sge::renderer::state::core::sampler::parameters(
              sge::renderer::state::core::sampler::address::default_(),
              sge::renderer::state::core::sampler::filter::mipmap())))
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::cg::manager::create_context(
    sge::renderer::context::core_ref const _context)
{
  return fcppt::unique_ptr_to_base<sge::scenic::render_context::base>(
      fcppt::make_unique_ptr<sge::scenic::render_context::cg::object>(
          fcppt::make_ref(*this), _context));
}

sge::scenic::render_context::cg::manager::~manager() = default;
