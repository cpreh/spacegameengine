//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_TEXTURE_COORDINATES_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_TEXTURE_COORDINATES_FWD_HPP_INCLUDED

#include <sge/sprite/types/basic/float_vector_fwd.hpp>
#include <sge/sprite/types/basic/homogenous_pair_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace types
{

template<
	typename TypeChoices
>
using texture_coordinates
=
sge::sprite::types::basic::homogenous_pair<
	sge::sprite::types::basic::float_vector<
		TypeChoices
	>
>;

}
}
}

#endif
