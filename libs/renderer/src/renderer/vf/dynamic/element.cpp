//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/vf/dynamic/any.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <fcppt/variant/comparison.hpp>

sge::renderer::vf::dynamic::element::element(sge::renderer::vf::dynamic::any const &_info)
    : info_(_info)
{
}

sge::renderer::vf::dynamic::any const &sge::renderer::vf::dynamic::element::info() const
{
  return this->info_;
}

bool sge::renderer::vf::dynamic::operator==(
    sge::renderer::vf::dynamic::element const &_left,
    sge::renderer::vf::dynamic::element const &_right)
{
  return _left.info() == _right.info();
}
