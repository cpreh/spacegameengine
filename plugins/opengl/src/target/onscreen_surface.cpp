//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/flipped.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_base_type.hpp>
#include <sge/opengl/convert/color_format.hpp>
#include <sge/opengl/convert/color_order.hpp>
#include <sge/opengl/target/onscreen_surface.hpp>
#include <sge/opengl/target/read_pixels.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_signed.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object_impl.hpp>

sge::opengl::target::onscreen_surface::onscreen_surface(awl::window::object_ref const _window)
    : sge::renderer::color_buffer::readable_surface(), window_(_window), buffer_()
{
}

sge::opengl::target::onscreen_surface::~onscreen_surface() = default;

sge::renderer::color_buffer::readable_surface::const_view
sge::opengl::target::onscreen_surface::lock_c(
    sge::renderer::color_buffer::readable_surface::lock_area const &_dest) const
{
  if (buffer_.has_value())
  {
    throw sge::renderer::exception(FCPPT_TEXT("renderer::target()::lock(): already locked!"));
  }

  buffer_type const &buffer{fcppt::optional::assign(
      buffer_,
      fcppt::container::buffer::read_from<buffer_type>(
          fcppt::math::dim::contents(_dest.size()) *
              sge::image::color::format_stride(this->format()),
          [&_dest](buffer_type::pointer const _data, buffer_type::size_type const _size)
          {
            sge::opengl::target::read_pixels(
                fcppt::math::vector::
                    structure_cast<sge::renderer::pixel_pos, fcppt::cast::size_fun>(
                        fcppt::math::vector::to_signed(_dest.pos())),
                fcppt::math::dim::structure_cast<sge::renderer::screen_size, fcppt::cast::size_fun>(
                    _dest.size()),
                sge::opengl::convert::color_order(onscreen_surface::gl_format()),
                sge::opengl::convert::color_base_type(onscreen_surface::gl_format()),
                _data);

            return _size;
          }))};

  return sge::image2d::view::flipped(sge::image2d::view::make_const(
      buffer.read_data(),
      _dest.size(),
      this->format(),
      fcppt::math::dim::null<sge::image2d::pitch>()));
}

void sge::opengl::target::onscreen_surface::unlock() const { buffer_ = fcppt::optional::nothing{}; }

sge::opengl::target::onscreen_surface::dim sge::opengl::target::onscreen_surface::size() const
{
  return fcppt::math::dim::structure_cast<dim, fcppt::cast::size_fun>(window_.get().size());
}

// Currently, 16bit and 32bit framebuffers are supported. rgba8 is enough to
// read both.

sge::opengl::color_format sge::opengl::target::onscreen_surface::gl_format()
{
  return sge::opengl::color_format::rgba8;
}

sge::image::color::format sge::opengl::target::onscreen_surface::format() const
{
  return sge::opengl::convert::color_format(onscreen_surface::gl_format());
}
