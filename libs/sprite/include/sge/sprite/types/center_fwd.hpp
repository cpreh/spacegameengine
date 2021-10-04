//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_CENTER_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_CENTER_FWD_HPP_INCLUDED

#include <sge/sprite/types/basic/unit_vector_fwd.hpp>
#include <sge/sprite/types/detail/center_tag.hpp>
#include <fcppt/strong_typedef_fwd.hpp>


namespace sge::sprite::types
{

template<
	typename TypeChoices
>
using center
=
fcppt::strong_typedef<
	sge::sprite::types::basic::unit_vector<
		TypeChoices
	>,
	sge::sprite::types::detail::center_tag
>;

}

#endif
