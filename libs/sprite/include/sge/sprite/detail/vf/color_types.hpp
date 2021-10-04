//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_COLOR_TYPES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_COLOR_TYPES_HPP_INCLUDED

#include <sge/sprite/detail/vf/color.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sge::sprite::detail::vf
{

template<
	typename Choices
>
using
color_types
=
fcppt::mpl::list::object<
	sge::sprite::detail::vf::color<
		Choices
	>
>;

}

#endif
