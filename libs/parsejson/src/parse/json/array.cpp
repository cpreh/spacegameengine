//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/recursive_comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::parse::json::array::array(sge::parse::json::element_vector &&_elements)
    : elements(std::move(_elements))
{
}

bool sge::parse::json::operator==(
    sge::parse::json::array const &_left, sge::parse::json::array const &_right)
{
  return _left.elements == _right.elements;
}
