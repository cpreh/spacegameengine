//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_CEGUI_IMPL_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/cegui/impl/batch.hpp>
#include <sge/cegui/impl/clip.hpp>
#include <sge/cegui/impl/geometry_buffer_fwd.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture_fwd.hpp>
#include <sge/cegui/impl/fwds/rectf_fwd.hpp>
#include <sge/cegui/impl/fwds/vector3f_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Quaternion.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace CEGUI
{
class RenderEffect;
struct Vertex;
class Texture;
}

namespace sge::cegui::impl
{

class geometry_buffer : public CEGUI::GeometryBuffer
{
  FCPPT_NONMOVABLE(geometry_buffer);

public:
  geometry_buffer(
      fcppt::log::object &, // NOLINT(google-runtime-references)
      sge::renderer::device::ffp_ref,
      sge::renderer::vertex::const_declaration_ref,
      fcppt::reference<sge::cegui::impl::optional_render_context_ref const>);

  ~geometry_buffer() override;

private:
  void draw() const override;

  void setTranslation(CEGUI::Vector3f const &) override;

  void setRotation(CEGUI::Quaternion const &) override;

  void setPivot(CEGUI::Vector3f const &) override;

  void setClippingRegion(CEGUI::Rectf const &) override;

  void appendVertex(CEGUI::Vertex const &) override;

  void appendGeometry(CEGUI::Vertex const *, CEGUI::uint vertex_count) override;

  void setActiveTexture(CEGUI::Texture *) override;

  void reset() override;

  [[nodiscard]] CEGUI::Texture *getActiveTexture() const override;

  [[nodiscard]] CEGUI::uint getVertexCount() const override;

  [[nodiscard]] CEGUI::uint getBatchCount() const override;

  void setRenderEffect(CEGUI::RenderEffect *) override;

  [[nodiscard]] CEGUI::RenderEffect *getRenderEffect() override;

  void setClippingActive(bool) override;

  [[nodiscard]] bool isClippingActive() const override;

  mutable fcppt::log::object log_;

  using batch_sequence = std::vector<sge::cegui::impl::batch>;

  batch_sequence batches_;

  sge::renderer::device::ffp_ref const renderer_;

  sge::renderer::vertex::const_declaration_ref const vertex_declaration_;

  using optional_texture_ref = fcppt::optional::reference<sge::cegui::impl::texture>;

  optional_texture_ref active_texture_;

  sge::renderer::vector3 translation_;

  sge::renderer::vector3 pivot_;

  CEGUI::Quaternion rotation_;

  sge::renderer::target::scissor_area scissor_area_;

  fcppt::reference<sge::cegui::impl::optional_render_context_ref const> const render_context_;

  sge::cegui::impl::clip clip_;

  using optional_render_effect_ref = fcppt::optional::reference<CEGUI::RenderEffect>;

  optional_render_effect_ref render_effect_;

  sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_on_;

  sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_off_;
};

}

#endif
