//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/vf/dynamic/element_count.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/strong_typedef_comparison.hpp>

sge::renderer::vf::dynamic::vector::vector(
    sge::renderer::vf::dynamic::element_type const _element_type,
    sge::renderer::vf::dynamic::element_count const _element_count)
    : element_type_(_element_type), element_count_(_element_count)
{
}

sge::renderer::vf::dynamic::element_type sge::renderer::vf::dynamic::vector::element_type() const
{
  return this->element_type_;
}

sge::renderer::vf::dynamic::element_count sge::renderer::vf::dynamic::vector::element_count() const
{
  return this->element_count_;
}

bool sge::renderer::vf::dynamic::operator==(
    sge::renderer::vf::dynamic::vector const &_left,
    sge::renderer::vf::dynamic::vector const &_right)
{
  return _left.element_type() == _right.element_type() &&
         _left.element_count() == _right.element_count();
}
