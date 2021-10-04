//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_CHOOSE_FFP_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_CHOOSE_FFP_HPP_INCLUDED

#include <sge/sprite/state/detail/needs_ffp.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::state::detail
{

template<
	typename StateChoices,
	typename Type1,
	typename Type2
>
using choose_ffp
=
std::conditional_t<
	sge::sprite::state::detail::needs_ffp<
		StateChoices
	>::type::value,
	Type1,
	Type2
>;

}

#endif
