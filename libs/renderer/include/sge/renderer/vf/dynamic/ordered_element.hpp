//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_ORDERED_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_ORDERED_ELEMENT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>

namespace sge::renderer::vf::dynamic
{

class ordered_element
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  ordered_element(sge::renderer::vf::dynamic::element const &, sge::renderer::vf::dynamic::offset);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::vf::dynamic::element const &
  element() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL sge::renderer::vf::dynamic::offset offset() const;

private:
  sge::renderer::vf::dynamic::element element_;

  sge::renderer::vf::dynamic::offset offset_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool operator==(
    sge::renderer::vf::dynamic::ordered_element const &,
    sge::renderer::vf::dynamic::ordered_element const &);

}

#endif
