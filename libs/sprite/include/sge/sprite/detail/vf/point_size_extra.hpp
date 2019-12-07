//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_VF_POINT_SIZE_EXTRA_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_POINT_SIZE_EXTRA_HPP_INCLUDED

#include <sge/sprite/config/is_point_size.hpp>
#include <sge/sprite/detail/vf/point_size.hpp>
#include <fcppt/not.hpp>
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
	typename Choices,
	typename Enable = void
>
struct point_size_extra;

template<
	typename Choices
>
struct point_size_extra<
	Choices,
	std::enable_if_t<
		sge::sprite::config::is_point_size<
			typename
			Choices::size_choice
		>::value
	>
>
{
	typedef
	metal::list<
		sge::sprite::detail::vf::point_size<
			Choices
		>
	>
	type;
};

template<
	typename Choices
>
struct point_size_extra<
	Choices,
	std::enable_if_t<
		fcppt::not_(
			sge::sprite::config::is_point_size<
				typename
				Choices::size_choice
			>::value
		)
	>
>
{
	typedef
	metal::list<>
	type;
};

}
}
}
}

#endif
