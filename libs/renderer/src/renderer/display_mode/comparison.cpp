//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/display_mode/comparison.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/optional/comparison.hpp>

bool sge::renderer::display_mode::operator==(
    sge::renderer::display_mode::object const &_left,
    sge::renderer::display_mode::object const &_right)
{
  return _left.pixel_size() == _right.pixel_size() && _left.dimensions() == _right.dimensions() &&
         _left.refresh_rate() == _right.refresh_rate();
}

bool sge::renderer::display_mode::operator!=(
    sge::renderer::display_mode::object const &_left,
    sge::renderer::display_mode::object const &_right)
{
  return !(_left == _right);
}
