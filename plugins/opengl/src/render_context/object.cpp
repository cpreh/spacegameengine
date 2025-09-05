//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/opengl/state/set_defaults.hpp>
#include <sge/opengl/state/core/blend/set.hpp>
#include <sge/opengl/state/core/depth_stencil/set.hpp>
#include <sge/opengl/state/core/rasterizer/set.hpp>
#include <sge/opengl/state/core/sampler/set.hpp>
#include <sge/opengl/state/ffp/alpha_test/set.hpp>
#include <sge/opengl/state/ffp/clip_plane/set.hpp>
#include <sge/opengl/state/ffp/fog/set.hpp>
#include <sge/opengl/state/ffp/lighting/set.hpp>
#include <sge/opengl/state/ffp/lighting/light/set.hpp>
#include <sge/opengl/state/ffp/lighting/material/set.hpp>
#include <sge/opengl/state/ffp/misc/set.hpp>
#include <sge/opengl/state/ffp/sampler/set.hpp>
#include <sge/opengl/state/ffp/transform/set.hpp>
#include <sge/opengl/target/base.hpp>
#include <sge/opengl/target/scoped.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/vertex/set_buffer.hpp>
#include <sge/opengl/vertex/set_declaration.hpp>
#include <sge/opengl/vertex/unset_buffer.hpp>
#include <sge/renderer/config.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/state/core/blend/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/ffp/alpha_test/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/clip_plane/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/lighting/material/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref_fwd.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)

#ifdef SGE_RENDERER_HAVE_CG
#include <sge/opengl/cg/program/activate.hpp>
#include <sge/opengl/cg/program/deactivate.hpp>
#include <sge/opengl/cg/texture/disable.hpp>
#include <sge/opengl/cg/texture/enable.hpp>
#include <sge/renderer/cg/const_loaded_program_ref.hpp>
#include <sge/renderer/cg/const_loaded_texture_ref.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif

sge::opengl::render_context::object::object(
    fcppt::log::object_reference const _log,
    sge::opengl::context::object_ref const _context,
    sge::renderer::target::base_ref const _target)
    : sge::renderer::context::ffp(),
      log_{_log},
      context_(_context),
      target_(_target),
      scoped_target_(fcppt::make_ref(dynamic_cast<sge::opengl::target::base &>(target_.get()))),
      scoped_offscreen_target_()
{
  sge::opengl::state::set_defaults(log_.get(), _context.get());
}

sge::opengl::render_context::object::~object() = default;

void sge::opengl::render_context::object::end_rendering() { scoped_target_.get().end_rendering(); }

sge::renderer::target::base &sge::opengl::render_context::object::target() { return target_.get(); }

void sge::opengl::render_context::object::clear(sge::renderer::clear::parameters const &_parameters)
{
  sge::opengl::clear::set(_parameters);
}

void sge::opengl::render_context::object::offscreen_target(
    sge::renderer::target::optional_offscreen_ref const &_new_target)
{
  fcppt::optional::maybe(
      _new_target,
      [this]
      {
        scoped_offscreen_target_ = optional_scoped_offscreen_target_ptr();

        scoped_target_.get().bind();
      },
      [this](fcppt::reference<sge::renderer::target::offscreen> const _target)
      {
        if (scoped_offscreen_target_.has_value())
        {
          throw sge::renderer::exception{FCPPT_TEXT("opengl: scoped_offscreen_target set")};
        }

        scoped_target_.get().unbind();

        scoped_offscreen_target_ = optional_scoped_offscreen_target_ptr(
            fcppt::make_unique_ptr<sge::opengl::target::scoped>(
                fcppt::make_ref(dynamic_cast<sge::opengl::target::base &>(_target.get()))));
      });
}

void sge::opengl::render_context::object::render_indexed(
    sge::renderer::index::buffer const &_index_buffer,
    sge::renderer::vertex::first const _first_vertex,
    sge::renderer::vertex::count const _num_vertices,
    sge::renderer::primitive_type const _primitive_type,
    sge::renderer::index::first const _first_index,
    sge::renderer::index::count const _num_indices)
{
  sge::opengl::draw_elements(
      log_.get(),
      context_.get(),
      _index_buffer,
      _first_vertex,
      _num_vertices,
      _primitive_type,
      _first_index,
      _num_indices);
}

void sge::opengl::render_context::object::render_nonindexed(
    sge::renderer::vertex::first const _first_vertex,
    sge::renderer::vertex::count const _num_vertices,
    sge::renderer::primitive_type const _primitive_type)
{
  sge::opengl::draw_arrays(log_.get(), _first_vertex, _num_vertices, _primitive_type);
}

void sge::opengl::render_context::object::activate_vertex_buffer(
    sge::renderer::vertex::const_buffer_ref const _vertex_buffer)
{
  sge::opengl::vertex::set_buffer(context_.get(), _vertex_buffer);
}

void sge::opengl::render_context::object::deactivate_vertex_buffer(
    sge::renderer::vertex::buffer const &_vertex_buffer)
{
  sge::opengl::vertex::unset_buffer(context_.get(), _vertex_buffer);
}

void sge::opengl::render_context::object::vertex_declaration(
    sge::renderer::vertex::const_optional_declaration_ref const &_vertex_declaration)
{
  sge::opengl::vertex::set_declaration(context_.get(), _vertex_declaration);
}

void sge::opengl::render_context::object::texture(
    sge::renderer::texture::const_optional_base_ref const &_texture,
    sge::renderer::texture::stage const _stage)
{
  sge::opengl::texture::activate(log_.get(), context_.get(), _texture, _stage);
}

void sge::opengl::render_context::object::blend_state(
    sge::renderer::state::core::blend::const_optional_object_ref const &_state)
{
  sge::opengl::state::core::blend::set(context_.get(), _state);
}

void sge::opengl::render_context::object::depth_stencil_state(
    sge::renderer::state::core::depth_stencil::const_optional_object_ref const &_state)
{
  sge::opengl::state::core::depth_stencil::set(context_.get(), _state);
}

void sge::opengl::render_context::object::rasterizer_state(
    sge::renderer::state::core::rasterizer::const_optional_object_ref const &_state)
{
  sge::opengl::state::core::rasterizer::set(context_.get(), _state);
}

void sge::opengl::render_context::object::sampler_state(
    sge::renderer::state::core::sampler::const_optional_object_ref_map const &_samplers)
{
  sge::opengl::state::core::sampler::set(log_.get(), context_.get(), _samplers);
}

void sge::opengl::render_context::object::alpha_test_state(
    sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::alpha_test::set(context_.get(), _state);
}

void sge::opengl::render_context::object::clip_plane_state(
    sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &_planes)
{
  sge::opengl::state::ffp::clip_plane::set(context_.get(), _planes);
}

void sge::opengl::render_context::object::fog_state(
    sge::renderer::state::ffp::fog::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::fog::set(context_.get(), _state);
}

void sge::opengl::render_context::object::lighting_state(
    sge::renderer::state::ffp::lighting::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::lighting::set(context_.get(), _state);
}

void sge::opengl::render_context::object::lights_state(
    sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_lights)
{
  sge::opengl::state::ffp::lighting::light::set(context_.get(), _lights);
}

void sge::opengl::render_context::object::material_state(
    sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::lighting::material::set(context_.get(), _state);
}

void sge::opengl::render_context::object::misc_state(
    sge::renderer::state::ffp::misc::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::misc::set(log_.get(), context_.get(), _state);
}

void sge::opengl::render_context::object::sampler_ffp_state(
    sge::renderer::state::ffp::sampler::const_object_ref_vector const &_samplers)
{
  sge::opengl::state::ffp::sampler::set(log_.get(), context_.get(), _samplers);
}

void sge::opengl::render_context::object::transform(
    sge::renderer::state::ffp::transform::mode const _mode,
    sge::renderer::state::ffp::transform::const_optional_object_ref const &_state)
{
  sge::opengl::state::ffp::transform::set(context_.get(), _mode, _state);
}

#ifdef SGE_RENDERER_HAVE_CG
void sge::opengl::render_context::object::set_cg_program(
    sge::renderer::cg::const_loaded_program_ref const _program)
{
  sge::opengl::cg::program::activate(_program.get());
}

void sge::opengl::render_context::object::unset_cg_program(
    sge::renderer::cg::loaded_program const &_program)
{
  sge::opengl::cg::program::deactivate(_program);
}

sge::renderer::texture::stage sge::opengl::render_context::object::set_cg_texture(
    sge::renderer::cg::const_loaded_texture_ref const _texture)
{
  return sge::opengl::cg::texture::enable(_texture.get());
}

void sge::opengl::render_context::object::unset_cg_texture(
    sge::renderer::cg::loaded_texture const &_texture)
{
  sge::opengl::cg::texture::disable(_texture);
}
#endif
