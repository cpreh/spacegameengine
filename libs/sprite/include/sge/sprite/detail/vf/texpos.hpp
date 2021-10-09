//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED

#include <sge/sprite/detail/vf/texpos_impl.hpp>

namespace sge::sprite::detail::vf
{

template <typename Choices>
using texpos = typename sge::sprite::detail::vf::texpos_impl<Choices>::type;

}

#endif
