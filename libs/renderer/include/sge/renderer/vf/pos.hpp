//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_POS_HPP_INCLUDED
#define SGE_RENDERER_VF_POS_HPP_INCLUDED

#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/pos_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/vf/vector_base.hpp>
#include <sge/renderer/vf/labels/pos.hpp>

namespace sge::renderer::vf
{

template <typename Format, sge::renderer::vf::element_count_type NumSubElements>
struct pos : sge::renderer::vf::vector_base<Format, NumSubElements>
{
  static_assert(
      sge::renderer::is_valid_float_type<Format>::value,
      "A vertex format pos can only be float or double");

  static_assert(
      NumSubElements >= 2 && NumSubElements <= 4,
      "A vertex format pos must have between 2 and 4 elements");

  using label = sge::renderer::vf::labels::pos;
};

}

#endif
