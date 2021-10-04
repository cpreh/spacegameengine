//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_TEXTURE_POINT_POS_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_TEXTURE_POINT_POS_FWD_HPP_INCLUDED

#include <sge/sprite/types/basic/float_vector_fwd.hpp>


namespace sge::sprite::types
{

template<
	typename TypeChoices
>
using texture_point_pos
=
sge::sprite::types::basic::float_vector<
	TypeChoices
>;

}

#endif
