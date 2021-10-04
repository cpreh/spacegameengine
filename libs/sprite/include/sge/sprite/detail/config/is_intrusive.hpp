//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_IS_INTRUSIVE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_IS_INTRUSIVE_HPP_INCLUDED

#include <sge/sprite/config/intrusive_fwd.hpp>
#include <fcppt/mpl/list/contains.hpp>


namespace sge::sprite::detail::config
{

template<
	typename Choices
>
using is_intrusive
=
fcppt::mpl::list::contains<
	typename
	Choices::optional_elements,
	sge::sprite::config::intrusive
>;

}

#endif
