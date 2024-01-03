//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <fcppt/strong_typedef_comparison.hpp>

sge::renderer::vf::dynamic::ordered_element::ordered_element(
    sge::renderer::vf::dynamic::element const &_element,
    sge::renderer::vf::dynamic::offset const _offset)
    : element_(_element), offset_(_offset)
{
}

sge::renderer::vf::dynamic::element const &
sge::renderer::vf::dynamic::ordered_element::element() const
{
  return element_;
}

sge::renderer::vf::dynamic::offset sge::renderer::vf::dynamic::ordered_element::offset() const
{
  return offset_;
}

bool sge::renderer::vf::dynamic::operator==(
    sge::renderer::vf::dynamic::ordered_element const &_left,
    sge::renderer::vf::dynamic::ordered_element const &_right)
{
  return _left.element() == _right.element() && _left.offset() == _right.offset();
}
