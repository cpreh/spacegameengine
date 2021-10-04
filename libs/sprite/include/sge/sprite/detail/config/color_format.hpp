//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_COLOR_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_COLOR_FORMAT_HPP_INCLUDED

#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/detail/config/find_if.hpp>
#include <sge/sprite/detail/config/lazy_head.hpp>
#include <fcppt/unit_fwd.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/list/empty.hpp>


namespace sge::sprite::detail::config
{

template<
	typename Choices
>
struct color_format
{
private:
	using
	list
	=
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_color
	>;

	template<
		typename Type
	>
	using
	get_color_format
	=
	typename
	Type::color_format;
public:
	// TODO(philipp): Make a function for this
	using
	type
	=
	fcppt::mpl::apply<
		fcppt::mpl::if_<
			fcppt::mpl::list::empty<
				list
			>,
			fcppt::mpl::constant<
				fcppt::unit
			>,
			sge::sprite::detail::config::lazy_head<
				get_color_format,
				list
			>
		>
	>;
};

}

#endif
