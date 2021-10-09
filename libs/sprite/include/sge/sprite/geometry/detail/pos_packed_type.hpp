//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_DETAIL_POS_PACKED_TYPE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_POS_PACKED_TYPE_HPP_INCLUDED

#include <sge/sprite/detail/vf/pos.hpp>

namespace sge::sprite::geometry::detail
{

template <typename Choices>
using pos_packed_type = typename sge::sprite::detail::vf::pos<Choices>::packed_type;

}

#endif
