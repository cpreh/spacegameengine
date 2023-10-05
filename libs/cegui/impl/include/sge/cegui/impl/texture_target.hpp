//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CEGUI_IMPL_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_CEGUI_IMPL_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture_fwd.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/cegui/impl/texture_target_fwd.hpp>
#include <sge/cegui/impl/fwds/sizef_fwd.hpp>
#include <sge/cegui/impl/fwds/vector2f_fwd.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/Size.h>
#include <CEGUI/TextureTarget.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>

namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Texture;
}

namespace sge::cegui::impl
{

class texture_target : public CEGUI::TextureTarget
{
  FCPPT_NONMOVABLE(texture_target);

public:
  texture_target(
      fcppt::log::object_reference,
      sge::cegui::impl::texture_parameters const &,
      sge::cegui::impl::optional_render_context_ref const &);

  ~texture_target() override;

private:
  void draw(CEGUI::GeometryBuffer const &) override;

  void draw(CEGUI::RenderQueue const &) override;

  void setArea(CEGUI::Rectf const &) override;

  [[nodiscard]] CEGUI::Rectf const &getArea() const override;

  [[nodiscard]] bool isImageryCache() const override;

  void activate() override;

  void deactivate() override;

  void unprojectPoint(
      CEGUI::GeometryBuffer const &buff,
      CEGUI::Vector2f const &p_in,
      CEGUI::Vector2f &p_out) const override;

  void clear() override;

  [[nodiscard]] CEGUI::Texture &getTexture() const override;

  void declareRenderSize(CEGUI::Sizef const &) override;

  [[nodiscard]] bool isRenderingInverted() const override;

  fcppt::log::object_reference const main_log_;

  fcppt::log::object log_;

  sge::cegui::impl::texture_parameters const texture_parameters_;

  using texture_unique_ptr = fcppt::unique_ptr<sge::cegui::impl::texture>;

  using optional_texture_unique_ptr = fcppt::optional::object<texture_unique_ptr>;

  sge::renderer::target::offscreen_unique_ptr const target_;

  sge::cegui::impl::optional_render_context_ref const &render_context_;

  optional_texture_unique_ptr texture_;

  CEGUI::Rectf area_;

  sge::renderer::caps::render_target_inverted const is_inverted_;

  sge::renderer::state::ffp::transform::optional_object_unique_ptr transform_state_;
};

}

#endif
