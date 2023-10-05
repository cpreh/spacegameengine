//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/exception.hpp>
#include <sge/cegui/impl/default_target.hpp>
#include <sge/cegui/impl/from_cegui_rect.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderQueue.h>
#include <CEGUI/RenderTarget.h>
#include <CEGUI/Vector.h>
#include <fcppt/config/external_end.hpp>

// cegui's internal OpenGL renderer uses a static viewport (I
// think). The area is initialized to the current viewport in the
// constructor and is changed only by setArea which is called by the
// renderer after a window size change.

// sge already provides this viewport-adaption technique so I just
// update the viewport variable when the viewport is requested.
sge::cegui::impl::default_target::default_target(
    fcppt::log::object &_log,
    sge::renderer::device::ffp_ref const _renderer,
    fcppt::reference<sge::cegui::impl::optional_render_context_ref const> const _render_context)
    : log_{_log, sge::log::default_parameters(fcppt::log::name{FCPPT_TEXT("default_target")})},
      renderer_(_renderer),
      viewport_(),
      transform_(),
      render_context_(_render_context)
{
}

sge::cegui::impl::default_target::~default_target() = default;

void sge::cegui::impl::default_target::draw(CEGUI::GeometryBuffer const &_buffer)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("default_target(") << this
                      << FCPPT_TEXT(")::draw(GeometryBuffer)"))

  _buffer.draw();
}

void sge::cegui::impl::default_target::draw(CEGUI::RenderQueue const &_queue)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("default_target(") << this
                      << FCPPT_TEXT(")::draw(RenderQueue)"))

  _queue.draw();
}

void sge::cegui::impl::default_target::setArea(CEGUI::Rectf const &_area)
{
  CEGUI::RenderTargetEventArgs args(this);

  viewport_ = _area;

  transform_ = fcppt::optional::map(
      sge::renderer::projection::orthogonal_viewport(
          sge::renderer::target::viewport(
              fcppt::math::box::
                  structure_cast<sge::renderer::pixel_rect, fcppt::cast::float_to_int_fun>(
                      sge::cegui::impl::from_cegui_rect(viewport_))),
          sge::renderer::projection::near(0.F),
          sge::renderer::projection::far(
              10.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
              )),
      [this](sge::renderer::matrix4 const &_matrix)
      {
        return renderer_.get().create_transform_state(
            sge::renderer::state::ffp::transform::parameters(_matrix));
      });

  this->fireEvent(CEGUI::RenderTarget::EventAreaChanged, args);
}

CEGUI::Rectf const &sge::cegui::impl::default_target::getArea() const { return viewport_; }

bool sge::cegui::impl::default_target::isImageryCache() const { return false; }

void sge::cegui::impl::default_target::activate()
{
  FCPPT_LOG_DEBUG(
      log_, fcppt::log::out << FCPPT_TEXT("default_target(") << this << FCPPT_TEXT(")::activate()"))

  fcppt::optional::maybe_void(
      transform_,
      [this](sge::renderer::state::ffp::transform::object_unique_ptr const &_transform)
      {
        fcppt::optional::to_exception(
            render_context_.get(),
            [] { return sge::cegui::exception{FCPPT_TEXT("Render context not set!")}; })
            .get()
            .transform(
                sge::renderer::state::ffp::transform::mode::projection,
                sge::renderer::state::ffp::transform::const_optional_object_ref(
                    fcppt::make_cref(*_transform)));
      });
}

void sge::cegui::impl::default_target::deactivate()
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("default_target(") << this << FCPPT_TEXT(")::deactivate()"))

  fcppt::optional::to_exception(
      render_context_.get(),
      [] { return sge::cegui::exception{FCPPT_TEXT("Render context not set!")}; })
      .get()
      .transform(
          sge::renderer::state::ffp::transform::mode::projection,
          sge::renderer::state::ffp::transform::const_optional_object_ref());
}

void sge::cegui::impl::default_target::unprojectPoint(
    CEGUI::GeometryBuffer const &, CEGUI::Vector2f const &, CEGUI::Vector2f &) const
{
  throw sge::cegui::exception{FCPPT_TEXT("default_target::unprojectPoint not implemented yet")};
}
