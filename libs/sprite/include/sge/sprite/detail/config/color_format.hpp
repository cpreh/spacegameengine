//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_COLOR_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_COLOR_FORMAT_HPP_INCLUDED

#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/detail/config/find_if.hpp>
#include <sge/sprite/detail/config/lazy_head.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/no_such_type.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
struct color_format
{
private:
	typedef
	sge::sprite::detail::config::find_if<
		typename
		Choices::optional_elements,
		sge::sprite::config::is_with_color
	>
	list;

	template<
		typename Type
	>
	using
	get_color_format
	=
	typename
	Type::color_format;
public:
	// TODO: Make a function for this
	typedef
	typename
	brigand::eval_if<
		std::is_same<
			list,
			brigand::list<>
		>,
		brigand::identity<
			brigand::no_such_type_
		>,
		sge::sprite::detail::config::lazy_head<
			get_color_format,
			list
		>
	>::type
	type;
};

}
}
}
}

#endif
