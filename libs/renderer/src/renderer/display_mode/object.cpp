//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>

sge::renderer::display_mode::object::object(
    sge::renderer::display_mode::pixel_size const _pixel_size,
    sge::renderer::display_mode::optional_dimensions const _dimensions,
    sge::renderer::display_mode::optional_refresh_rate const _refresh_rate)
    : pixel_size_(_pixel_size), dimensions_(_dimensions), refresh_rate_(_refresh_rate)
{
}

sge::renderer::display_mode::pixel_size const &
sge::renderer::display_mode::object::pixel_size() const
{
  return pixel_size_;
}

sge::renderer::display_mode::optional_dimensions const &
sge::renderer::display_mode::object::dimensions() const
{
  return dimensions_;
}

sge::renderer::display_mode::optional_refresh_rate
sge::renderer::display_mode::object::refresh_rate() const
{
  return refresh_rate_;
}
