//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_DEPTH_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_DEPTH_HPP_INCLUDED

#include <sge/sprite/config/with_depth.hpp>
#include <fcppt/mpl/list/contains.hpp>


namespace sge::sprite::detail::config
{

template<
	typename Choices
>
using has_depth
=
fcppt::mpl::list::contains<
	typename
	Choices::optional_elements,
	sge::sprite::config::with_depth
>;

}

#endif
