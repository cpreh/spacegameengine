//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_BASIC_FLOAT_VECTOR_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_BASIC_FLOAT_VECTOR_FWD_HPP_INCLUDED

#include <sge/sprite/types/basic/vector_fwd.hpp>


namespace sge::sprite::types::basic
{

template<
	typename TypeChoices
>
using float_vector
=
sge::sprite::types::basic::vector<
	typename TypeChoices::float_type
>;

}

#endif
