//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_OBJECT_HPP_INCLUDED

#include <sge/renderer/matrix4_fwd.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/state/core/blend/object_unique_ptr.hpp>
#include <sge/renderer/state/core/blend/scoped.hpp>
#include <sge/renderer/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/state/core/rasterizer/scoped.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/scoped.hpp>
#include <sge/renderer/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/light/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/scoped_buffer_fwd.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/scenic/index_buffer_range_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/render_context/base.hpp>
#include <sge/scenic/render_context/transform_matrix_type.hpp>
#include <sge/scenic/render_context/ffp/manager_fwd.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/render_context/material/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::scenic::render_context::ffp
{
class object : public sge::scenic::render_context::base
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_SCENIC_DETAIL_SYMBOL
  object(
      fcppt::reference<sge::scenic::render_context::ffp::manager>, sge::renderer::context::ffp_ref);

  SGE_SCENIC_DETAIL_SYMBOL
  void transform(
      sge::scenic::render_context::transform_matrix_type, sge::renderer::matrix4 const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  void material(sge::scenic::render_context::material::object const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  void lights(sge::scenic::render_context::light::sequence const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  void vertex_buffer(sge::renderer::vertex::buffer const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  void fog(sge::scenic::render_context::fog::optional_properties const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  void
  render(sge::renderer::index::buffer const &, sge::scenic::index_buffer_range const &) override;

  SGE_SCENIC_DETAIL_SYMBOL
  sge::renderer::target::base &target() override;

  SGE_SCENIC_DETAIL_SYMBOL
  ~object() override;

private:
  friend class sge::scenic::render_context::ffp::manager;

  fcppt::reference<sge::scenic::render_context::ffp::manager> const manager_;

  sge::renderer::context::ffp_ref const context_;

  sge::renderer::vertex::scoped_declaration scoped_vertex_declaration_;

  using optional_transform_unique_ptr =
      fcppt::optional::object<sge::renderer::state::ffp::transform::object_unique_ptr>;

  optional_transform_unique_ptr projection_transform_;

  optional_transform_unique_ptr world_transform_;

  sge::renderer::vertex::count current_vertex_buffer_size_;

  using scoped_vertex_buffer_unique_ptr = fcppt::unique_ptr<sge::renderer::vertex::scoped_buffer>;

  using optional_scoped_vertex_buffer_unique_ptr =
      fcppt::optional::object<scoped_vertex_buffer_unique_ptr>;

  optional_scoped_vertex_buffer_unique_ptr current_vertex_buffer_;

  using optional_material_unique_ptr =
      fcppt::optional::object<sge::renderer::state::ffp::lighting::material::object_unique_ptr>;

  optional_material_unique_ptr current_material_;

  using light_ptr_vector =
      std::vector<sge::renderer::state::ffp::lighting::light::object_unique_ptr>;

  light_ptr_vector lights_;

  sge::renderer::state::core::sampler::object_unique_ptr const diffuse_texture_sampler_;

  sge::renderer::state::core::sampler::scoped scoped_sampler_;

  sge::renderer::state::ffp::lighting::object_unique_ptr const current_lighting_;

  sge::renderer::state::core::depth_stencil::object_unique_ptr const depth_stencil_state_;

  sge::renderer::state::core::blend::object_unique_ptr const blend_state_;

  sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_state_;

  sge::renderer::state::core::depth_stencil::scoped scoped_depth_stencil_state_;

  sge::renderer::state::core::blend::scoped scoped_blend_state_;

  sge::renderer::state::core::rasterizer::scoped scoped_rasterizer_state_;
};

}

#endif
