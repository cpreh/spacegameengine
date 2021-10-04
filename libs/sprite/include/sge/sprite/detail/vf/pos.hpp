//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_POS_HPP_INCLUDED

#include <sge/renderer/vf/pos.hpp>


namespace sge::sprite::detail::vf
{

template<
	typename Choices
>
using
pos
=
sge::renderer::vf::pos<
	typename
	Choices::type_choices::float_type,
	3
>;

}

#endif
