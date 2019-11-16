//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PROCESS_DO_DEFAULT_SORT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PROCESS_DO_DEFAULT_SORT_HPP_INCLUDED

#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace process
{

template<
	typename Choices,
	typename Compare
>
using do_default_sort
=
std::conjunction<
	sge::sprite::detail::config::has_texture_levels<
		Choices
	>,
	std::negation<
		typename Compare:: template is_trivial<
			Choices
		>::type
	>
>;

}
}
}
}

#endif
