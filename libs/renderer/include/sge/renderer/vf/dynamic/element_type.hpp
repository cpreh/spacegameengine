//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VF_DYNAMIC_ELEMENT_TYPE_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_ELEMENT_TYPE_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/element_type_fwd.hpp>

namespace sge::renderer::vf::dynamic
{

enum class element_type
{
  float_,
  double_,
  byte,
  ubyte,
  short_,
  ushort,
  int_,
  uint
};

}

#endif
