//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/strong_typedef_comparison.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::renderer::vf::dynamic::part::part(
    sge::renderer::vf::dynamic::element_list const &_elements,
    sge::renderer::vf::dynamic::offset_list const &_offsets)
    : elements_(
          [&_elements, &_offsets]
          {
            if (_elements.size() + 1U != _offsets.size())
            {
              throw sge::renderer::exception{
                  FCPPT_TEXT("dynamic::format: Invalid sizes of vectors!")};
            }

            return fcppt::algorithm::map<sge::renderer::vf::dynamic::ordered_element_list>(
                fcppt::make_int_range_count(_elements.size()),
                [&_elements,
                 &_offsets](sge::renderer::vf::dynamic::element_list::size_type const _index) {
                  return sge::renderer::vf::dynamic::ordered_element(
                      _elements[_index], _offsets[_index]);
                });
          }()),
      stride_(sge::renderer::vf::dynamic::stride(_offsets.back().get()))
{
}

sge::renderer::vf::dynamic::part::part(
    sge::renderer::vf::dynamic::ordered_element_list &&_elements,
    sge::renderer::vf::dynamic::stride const _stride)
    : elements_{std::move(_elements)}, stride_{_stride}
{
}

sge::renderer::vf::dynamic::ordered_element_list const &
sge::renderer::vf::dynamic::part::elements() const
{
  return elements_;
}

sge::renderer::vf::dynamic::stride sge::renderer::vf::dynamic::part::stride() const
{
  return stride_;
}

bool sge::renderer::vf::dynamic::operator==(
    sge::renderer::vf::dynamic::part const &_left, sge::renderer::vf::dynamic::part const &_right)
{
  return _left.elements() == _right.elements() && _left.stride() == _right.stride();
}
