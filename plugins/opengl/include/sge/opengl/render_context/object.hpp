//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/target/scoped.hpp>
#include <sge/renderer/config.hpp> // IWYU pragma: keep
#include <sge/renderer/primitive_type_fwd.hpp>
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
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <sge/renderer/target/optional_offscreen_ref_fwd.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_decl.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/renderer/cg/const_loaded_program_ref.hpp>
#include <sge/renderer/cg/const_loaded_texture_ref.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif

namespace sge::opengl::render_context
{

class object : public sge::renderer::context::ffp
{
  FCPPT_NONMOVABLE(object);

public:
  object(
      fcppt::log::object_reference,
      sge::opengl::context::object_ref,
      sge::renderer::target::base_ref);

  ~object() override;

  void end_rendering();

private:
  sge::renderer::target::base &target() override;

  void clear(sge::renderer::clear::parameters const &) override;

  void offscreen_target(sge::renderer::target::optional_offscreen_ref const &) override;

  void render_indexed(
      sge::renderer::index::buffer const &,
      sge::renderer::vertex::first,
      sge::renderer::vertex::count,
      sge::renderer::primitive_type,
      sge::renderer::index::first,
      sge::renderer::index::count) override;

  void render_nonindexed(
      sge::renderer::vertex::first,
      sge::renderer::vertex::count,
      sge::renderer::primitive_type) override;

  void activate_vertex_buffer(sge::renderer::vertex::const_buffer_ref) override;

  void deactivate_vertex_buffer(sge::renderer::vertex::buffer const &) override;

  void vertex_declaration(sge::renderer::vertex::const_optional_declaration_ref const &) override;

  void texture(
      sge::renderer::texture::const_optional_base_ref const &,
      sge::renderer::texture::stage) override;

  void blend_state(sge::renderer::state::core::blend::const_optional_object_ref const &) override;

  void depth_stencil_state(
      sge::renderer::state::core::depth_stencil::const_optional_object_ref const &) override;

  void rasterizer_state(
      sge::renderer::state::core::rasterizer::const_optional_object_ref const &) override;

  void sampler_state(
      sge::renderer::state::core::sampler::const_optional_object_ref_map const &) override;

  void alpha_test_state(
      sge::renderer::state::ffp::alpha_test::const_optional_object_ref const &) override;

  void
  clip_plane_state(sge::renderer::state::ffp::clip_plane::const_object_ref_vector const &) override;

  void fog_state(sge::renderer::state::ffp::fog::const_optional_object_ref const &) override;

  void
  lighting_state(sge::renderer::state::ffp::lighting::const_optional_object_ref const &) override;

  void lights_state(
      sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &) override;

  void material_state(
      sge::renderer::state::ffp::lighting::material::const_optional_object_ref const &) override;

  void misc_state(sge::renderer::state::ffp::misc::const_optional_object_ref const &) override;

  void
  sampler_ffp_state(sge::renderer::state::ffp::sampler::const_object_ref_vector const &) override;

  void transform(
      sge::renderer::state::ffp::transform::mode,
      sge::renderer::state::ffp::transform::const_optional_object_ref const &) override;

#if defined(SGE_RENDERER_HAVE_CG)
  void set_cg_program(sge::renderer::cg::const_loaded_program_ref) override;

  void unset_cg_program(sge::renderer::cg::loaded_program const &) override;

  sge::renderer::texture::stage
      set_cg_texture(sge::renderer::cg::const_loaded_texture_ref) override;

  void unset_cg_texture(sge::renderer::cg::loaded_texture const &) override;
#endif

  fcppt::log::object_reference const log_;

  sge::opengl::context::object_ref const context_;

  sge::renderer::target::base_ref const target_;

  sge::opengl::target::scoped const scoped_target_;

  using scoped_offscreen_target_ptr = fcppt::unique_ptr<sge::opengl::target::scoped>;

  using optional_scoped_offscreen_target_ptr = fcppt::optional::object<scoped_offscreen_target_ptr>;

  optional_scoped_offscreen_target_ptr scoped_offscreen_target_;
};

}

#endif
