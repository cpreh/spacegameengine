//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED

#include <sge/sprite/detail/config/has_custom_texture_point_pos.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_size.hpp>
#include <sge/sprite/detail/vf/texture_point_pos.hpp>
#include <sge/sprite/detail/vf/texture_point_size.hpp>
#include <fcppt/mpl/apply.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::detail::vf
{

template<
	typename Choices
>
using
texture_point
=
fcppt::mpl::list::append<
	std::conditional_t<
		sge::sprite::detail::config::has_custom_texture_point_pos<
			Choices
		>::value,
		fcppt::mpl::list::object<
			sge::sprite::detail::vf::texture_point_pos<
				Choices
			>
		>,
		fcppt::mpl::list::object<>
	>,
	fcppt::mpl::apply<
		std::conditional_t<
			sge::sprite::detail::config::has_custom_texture_point_size<
				Choices
			>::value,
			fcppt::mpl::bind<
				fcppt::mpl::lambda<
					sge::sprite::detail::vf::texture_point_size
				>,
				fcppt::mpl::constant<
					Choices
				>
			>,
			fcppt::mpl::constant<
				fcppt::mpl::list::object<>
			>
		>
	>
>;

}

#endif
