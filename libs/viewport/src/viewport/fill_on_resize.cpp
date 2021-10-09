//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/window/dim.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>

sge::viewport::resize_callback sge::viewport::fill_on_resize()
{
  return sge::viewport::resize_callback{
      [](awl::window::event::resize const &_resize)
      {
        return sge::renderer::target::viewport(sge::renderer::pixel_rect(
            fcppt::math::vector::null<sge::renderer::pixel_rect::vector>(),
            fcppt::math::dim::structure_cast<
                sge::renderer::pixel_rect::dim,
                fcppt::cast::to_signed_fun>(
                fcppt::math::dim::structure_cast<sge::renderer::screen_size, fcppt::cast::size_fun>(
                    _resize.dim()))));
      }};
}
