//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_VF_FORMAT_PART_FROM_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_FORMAT_PART_FROM_OBJECT_HPP_INCLUDED

#include <sge/sprite/detail/vf/format_part.hpp>

namespace sge::sprite::detail::vf
{

template <typename Object>
using format_part_from_object =
    typename sge::sprite::detail::vf::format_part<typename Object::choices>::type;

}

#endif
