//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_TYPES_POS_OR_CENTER_FWD_HPP_INCLUDED
#define SGE_SPRITE_TYPES_POS_OR_CENTER_FWD_HPP_INCLUDED

#include <sge/sprite/types/center_fwd.hpp>
#include <sge/sprite/types/pos_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge::sprite::types
{

template<
	typename TypeChoices
>
using
pos_or_center
=
fcppt::variant::object<
	sge::sprite::types::pos<
		TypeChoices
	>,
	sge::sprite::types::center<
		TypeChoices
	>
>;

}

#endif
