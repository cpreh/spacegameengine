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
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace vf
{

template<
	typename Choices
>
using
texture_point
=
metal::join<
	std::conditional_t<
		sge::sprite::detail::config::has_custom_texture_point_pos<
			Choices
		>::value,
		metal::list<
			sge::sprite::detail::vf::texture_point_pos<
				Choices
			>
		>,
		metal::list<>
	>,
	metal::invoke<
		std::conditional_t<
			sge::sprite::detail::config::has_custom_texture_point_size<
				Choices
			>::value,
			metal::bind<
				metal::lambda<
					sge::sprite::detail::vf::texture_point_size
				>,
				metal::always<
					Choices
				>
			>,
			metal::always<
				metal::list<>
			>
		>
	>
>;

}
}
}
}

#endif
