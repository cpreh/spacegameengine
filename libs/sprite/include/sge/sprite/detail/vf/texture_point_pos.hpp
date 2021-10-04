//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/detail/vf/texpos.hpp>


namespace sge::sprite::detail::vf
{

template<
	typename Choices
>
using texture_point_pos
=
sge::sprite::detail::vf::texpos<
	Choices
>;

}

#endif
