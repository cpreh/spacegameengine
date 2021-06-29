//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED

#include <sge/sprite/detail/config/find_texture_config.hpp>
#include <sge/sprite/detail/config/lazy_head.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
#include <fcppt/unit_fwd.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/if.hpp>
#include <fcppt/mpl/list/empty.hpp>


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

	using
	texture_list
	=
	typename
	sge::sprite::detail::config::find_texture_config<
		Choices
	>::type;
public:
	using
	type
	=
	fcppt::mpl::apply<
		fcppt::mpl::if_<
			fcppt::mpl::list::empty<
				texture_list
			>,
			fcppt::mpl::constant<
				fcppt::unit
			>,
			sge::sprite::detail::config::lazy_head<
				obtain_ref_type,
				texture_list
			>
		>
	>;
};

}
}
}
}

#endif
