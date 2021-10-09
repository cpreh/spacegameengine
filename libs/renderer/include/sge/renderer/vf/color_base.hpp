//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_COLOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_COLOR_BASE_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <mizuiro/color/object_impl.hpp>

namespace sge::renderer::vf
{

template <typename Format>
struct color_base
{
  using subelement_type = typename Format::channel_type;

  using packed_type = mizuiro::color::object<Format>;

  static sge::renderer::vf::element_count_type const num_subelements = Format::element_count;
};

}

#endif
