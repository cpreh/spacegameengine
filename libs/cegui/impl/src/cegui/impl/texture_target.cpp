//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/exception.hpp>
#include <sge/cegui/impl/from_cegui_rect.hpp>
#include <sge/cegui/impl/from_cegui_size.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/cegui/impl/texture_target.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/color_buffer/writable_surface.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/offscreen.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/box/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderQueue.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Vector.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

sge::cegui::impl::texture_target::texture_target(
    fcppt::log::object_reference const _main_log,
    sge::cegui::impl::texture_parameters const &_texture_parameters,
    sge::cegui::impl::optional_render_context_ref const &_render_context)
    : main_log_{_main_log},
      log_{
          _main_log.get(),
          sge::log::default_parameters(fcppt::log::name{FCPPT_TEXT("texture_target")})},
      texture_parameters_(_texture_parameters),
      target_(texture_parameters_.renderer().create_target()),
      render_context_(_render_context),
      texture_(),
      // This is exactly what cegui does and it avoids certain bugs :/
      area_(0, 0, 0, 0),
      is_inverted_(_texture_parameters.renderer().caps().render_target_inverted()),
      transform_state_(){FCPPT_LOG_DEBUG(
          log_,
          fcppt::log::out << FCPPT_TEXT("texture_target(") << this
                          << FCPPT_TEXT(")::texture_target"))}

      sge::cegui::impl::texture_target::~texture_target() = default;

void sge::cegui::impl::texture_target::draw(CEGUI::GeometryBuffer const &_buffer)
{
  if (!fcppt::optional::to_exception(
           this->texture_,
           [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; })
           ->impl()
           .has_value())
  {
    return;
  }

  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("texture_target(") << this
                      << FCPPT_TEXT(")::draw(GeometryBuffer)"))

  _buffer.draw();
}

void sge::cegui::impl::texture_target::draw(CEGUI::RenderQueue const &_queue)
{
  if (!fcppt::optional::to_exception(
           texture_,
           [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; })
           ->impl()
           .has_value())
  {
    return;
  }

  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("texture_target(") << this
                      << FCPPT_TEXT(")::draw(RenderQueue)"))

  _queue.draw();
}

void sge::cegui::impl::texture_target::setArea(CEGUI::Rectf const &_area)
{
  {
    auto const area(
        fcppt::math::box::structure_cast<sge::renderer::pixel_rect, fcppt::cast::float_to_int_fun>(
            sge::cegui::impl::from_cegui_rect(_area)));

    FCPPT_LOG_DEBUG(
        log_,
        fcppt::log::out << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::setArea(")
                        << area << FCPPT_TEXT(')'))
  }

  area_ = _area;

  if (area_.getWidth() * area_.getHeight() <
      0.01F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  )
  {
    transform_state_ = sge::renderer::state::ffp::transform::optional_object_unique_ptr();

    return;
  }

  transform_state_ = sge::renderer::state::ffp::transform::optional_object_unique_ptr(
      texture_parameters_.renderer().create_transform_state(
          sge::renderer::state::ffp::transform::parameters(sge::renderer::projection::orthogonal(
              sge::cegui::impl::from_cegui_rect(area_),
              sge::renderer::projection::near(0.F),
              sge::renderer::projection::far(
                  2.F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                  )))));
}

CEGUI::Rectf const &sge::cegui::impl::texture_target::getArea() const { return area_; }

bool sge::cegui::impl::texture_target::isImageryCache() const { return true; }

void sge::cegui::impl::texture_target::activate()
{
  if (!fcppt::optional::to_exception(
           texture_,
           [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; })
           ->impl()
           .has_value())
  {
    return;
  }

  FCPPT_LOG_DEBUG(
      log_, fcppt::log::out << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::activate()"))

  sge::renderer::context::ffp &render_context{
      fcppt::optional::to_exception(
          render_context_,
          []
          { return sge::cegui::exception{FCPPT_TEXT("Texture target render context not set!")}; })
          .get()};

  render_context.offscreen_target(
      sge::renderer::target::optional_offscreen_ref(fcppt::make_ref(*target_)));

  target_->viewport(sge::renderer::target::viewport(
      fcppt::math::box::structure_cast<sge::renderer::pixel_rect, fcppt::cast::float_to_int_fun>(
          sge::cegui::impl::from_cegui_rect(area_))));

  render_context.transform(
      sge::renderer::state::ffp::transform::mode::projection,
      sge::renderer::state::ffp::transform::const_optional_object_ref{
          fcppt::make_cref(*fcppt::optional::to_exception(
              transform_state_,
              [] {
                return sge::cegui::exception{FCPPT_TEXT("Texture target transform state not set!")};
              }))});
}

void sge::cegui::impl::texture_target::deactivate()
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::deactivate()"))

  if (!fcppt::optional::to_exception(
           texture_,
           [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; })
           ->impl()
           .has_value())
  {
    return;
  }

  sge::renderer::context::ffp &render_context{
      fcppt::optional::to_exception(
          render_context_,
          []
          { return sge::cegui::exception{FCPPT_TEXT("Texture target render context not set!")}; })
          .get()};

  render_context.transform(
      sge::renderer::state::ffp::transform::mode::projection,
      sge::renderer::state::ffp::transform::const_optional_object_ref());

  render_context.offscreen_target(sge::renderer::target::optional_offscreen_ref());
}

void sge::cegui::impl::texture_target::unprojectPoint(
    CEGUI::GeometryBuffer const &, CEGUI::Vector2f const &, CEGUI::Vector2f &) const
{
  throw sge::cegui::exception{FCPPT_TEXT("texture_target::unprojectPoint not implemented yet")};
}

void sge::cegui::impl::texture_target::clear()
{
  FCPPT_LOG_DEBUG(
      log_, fcppt::log::out << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::clear()"))

  sge::cegui::impl::texture &texture{*fcppt::optional::to_exception(
      texture_,
      [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; })};

  fcppt::optional::maybe_void(
      texture.impl(),
      [this](fcppt::reference<sge::renderer::texture::planar> const _texture)
      {
        // Make sure we clear everything

        sge::renderer::pixel_rect const rect(
            fcppt::math::vector::null<sge::renderer::pixel_rect::vector>(),
            fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim, fcppt::cast::size_fun>(
                fcppt::math::dim::to_signed(_texture.get().size())));

        target_->viewport(sge::renderer::target::viewport(rect));

        target_->scissor_area(sge::renderer::target::scissor_area(rect));

        target_->clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::transparent()}));
      });
}

CEGUI::Texture &sge::cegui::impl::texture_target::getTexture() const
{
  return *fcppt::optional::to_exception(
      this->texture_,
      [] { return sge::cegui::exception{FCPPT_TEXT("Texture target texture not set!")}; });
}

void sge::cegui::impl::texture_target::declareRenderSize(CEGUI::Sizef const &_size)
{
  FCPPT_LOG_DEBUG(
      log_,
      fcppt::log::out << FCPPT_TEXT("texture_target(") << this
                      << FCPPT_TEXT(")::declareRenderSize(")
                      << sge::cegui::impl::from_cegui_size(_size) << FCPPT_TEXT(')'))

  this->setArea(CEGUI::Rectf(area_.getPosition(), _size));

  CEGUI::String const texture_name("sge texture target");

  // The size here could be (0,0), for example if the viewport hasn't
  // been initialized yet. If that's the case, create an empty texture.

  using signed_dim = fcppt::math::dim::static_<std::make_signed_t<sge::renderer::size_type>, 2>;

  texture_unique_ptr &texture(fcppt::optional::assign(
      texture_,
      fcppt::math::dim::structure_cast<signed_dim, fcppt::cast::float_to_int_fun>(
          sge::cegui::impl::from_cegui_size(_size)) == fcppt::math::dim::null<signed_dim>()
          ? fcppt::make_unique_ptr<sge::cegui::impl::texture>(
                main_log_.get(), texture_parameters_, texture_name)
          : fcppt::make_unique_ptr<sge::cegui::impl::texture>(
                main_log_.get(),
                texture_parameters_,
                texture_name,
                _size,
                sge::renderer::texture::capabilities_field{
                    sge::renderer::texture::capabilities::render_target})));

  fcppt::optional::maybe_void(
      texture->impl(),
      [this](fcppt::reference<sge::renderer::texture::planar> const _texture)
      {
        target_->color_surface(
            sge::renderer::color_buffer::optional_surface_ref(
                fcppt::reference_to_base<sge::renderer::color_buffer::surface>(fcppt::make_ref(
                    _texture.get().level(sge::renderer::texture::mipmap::level(0U))))),
            sge::renderer::target::surface_index(0U));

        this->clear();
      });
}

bool sge::cegui::impl::texture_target::isRenderingInverted() const { return is_inverted_.get(); }
