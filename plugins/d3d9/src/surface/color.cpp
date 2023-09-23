//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/make_pitch_2d.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/devicefuncs/create_offscreen_plain_surface.hpp>
#include <sge/d3d9/devicefuncs/get_render_target_data.hpp>
#include <sge/d3d9/surface/color.hpp>
#include <sge/d3d9/surface/color_create_function.hpp>
#include <sge/d3d9/surface/color_holder.hpp>
#include <sge/d3d9/surface/d3d_unique_ptr.hpp>
#include <sge/d3d9/surface/optional_d3d_unique_ptr.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/unlock_rect.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::d3d9::surface::color::color(
    IDirect3DDevice9 &_device,
    sge::image::color::format const _format,
    sge::d3d9::surface::color_create_function const &_create)
    : sge::d3d9::resource(sge::d3d9::needs_reset::yes),
      device_(_device),
      create_(_create),
      format_(_format),
      color_holder_(),
      temp_surface_()
{
  this->init();
}

sge::d3d9::surface::color::~color() {}

sge::d3d9::surface::color::const_view
sge::d3d9::surface::color::lock_c(lock_area const &_rect) const
{
  if (this->color_holder().is_render_target())
  {
    FCPPT_PP_PUSH_WARNING
    FCPPT_PP_IGNORE_DANGLING_REFERENCE
    sge::d3d9::surface::d3d_unique_ptr const &temp_surface{fcppt::optional::assign(
        temp_surface_,
        sge::d3d9::devicefuncs::create_offscreen_plain_surface(
            device_, this->color_holder().size(), format_, D3DPOOL_SYSTEMMEM))};
    FCPPT_PP_POP_WARNING

    sge::d3d9::devicefuncs::get_render_target_data(device_, this->surface(), *temp_surface);
  }

  D3DLOCKED_RECT const locked_rect(sge::d3d9::surfacefuncs::lock_rect(
      this->lock_surface(),
      // TODO
      this->size() == _rect.size() ? sge::d3d9::optional_lock_rect()
                                   : sge::d3d9::optional_lock_rect(_rect),
      fcppt::strong_typedef_construct_cast<sge::d3d9::lock_flags, fcppt::cast::size_fun>(
          fcppt::cast::to_unsigned(D3DLOCK_READONLY))));

  return const_view(sge::image2d::view::make_const(
      fcppt::cast::from_void_ptr<sge::renderer::const_raw_pointer>(locked_rect.pBits),
      _rect.size(),
      format_,
      sge::d3d9::make_pitch_2d(locked_rect, _rect.size(), format_)));
}

void sge::d3d9::surface::color::unlock() const
{
  sge::d3d9::surfacefuncs::unlock_rect(this->lock_surface());

  if (this->color_holder().is_render_target())
  {
    temp_surface_ = sge::d3d9::surface::optional_d3d_unique_ptr();
  }
}

sge::d3d9::surface::color::dim sge::d3d9::surface::color::size() const
{
  return this->color_holder().size();
}

sge::image::color::format sge::d3d9::surface::color::format() const { return format_; }

IDirect3DSurface9 &sge::d3d9::surface::color::surface() const
{
  return this->color_holder().get();
}

IDirect3DSurface9 &sge::d3d9::surface::color::lock_surface() const
{
  return this->color_holder().is_render_target() ? *fcppt::optional::to_exception(
                                                       this->temp_surface_,
                                                       [] {
                                                         return sge::renderer::exception{FCPPT_TEXT(
                                                             "d3d9 color temp surface not set!")};
                                                       })
                                                 : this->surface();
}

sge::d3d9::surface::color_holder &sge::d3d9::surface::color::color_holder() const
{
  return *fcppt::optional::to_exception(
      this->color_holder_,
      [] { return sge::renderer::exception{FCPPT_TEXT("d3d9 color surface not set!")}; });
}

void sge::d3d9::surface::color::init()
{
  color_holder_ = optional_color_holder_unique_ptr(
      fcppt::make_unique_ptr<sge::d3d9::surface::color_holder>(create_()));
}

void sge::d3d9::surface::color::on_loss()
{
  temp_surface_ = sge::d3d9::surface::optional_d3d_unique_ptr();

  color_holder_ = optional_color_holder_unique_ptr();
}

void sge::d3d9::surface::color::on_reset() { this->init(); }
