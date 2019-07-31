//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED

#include <sge/sprite/detail/config/find_texture_config.hpp>
#include <sge/sprite/detail/config/lazy_head.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
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
struct texture_ref
{
private:
	template<
		typename Element
	>
	using
	obtain_ref_type
	=
	typename
	sge::sprite::detail::primitives::texture_ref_type<
		Element::ownership::value
	>::type;

	typedef
	typename
	sge::sprite::detail::config::find_texture_config<
		Choices
	>::type
	texture_list;
public:
	typedef
	typename
	brigand::eval_if<
		std::is_same<
			texture_list,
			brigand::list<>
		>,
		brigand::identity<
			brigand::no_such_type_
		>,
		sge::sprite::detail::config::lazy_head<
			obtain_ref_type,
			texture_list
		>
	>::type
	type;
};

}
}
}
}

#endif
