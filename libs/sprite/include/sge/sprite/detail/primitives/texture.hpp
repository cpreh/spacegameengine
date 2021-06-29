//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_HPP_INCLUDED

#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_ownership_fwd.hpp>
#include <sge/sprite/detail/primitives/texture_coordinates.hpp>
#include <sge/sprite/detail/primitives/texture_ptr.hpp>
#include <sge/sprite/detail/primitives/texture_repetition.hpp>
#include <fcppt/mpl/list/append.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_coordinates,
	sge::sprite::config::texture_ownership
>
struct texture;

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::custom,
	Ownership
>
{
	using
	type
	=
	fcppt::mpl::list::append<
		typename
		sge::sprite::detail::primitives::texture_ptr<
			Choices,
			TextureLevels,
			Ownership
		>::type,
		typename
		sge::sprite::detail::primitives::texture_coordinates<
			Choices,
			TextureLevels
		>::type
	>;
};

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::repetition,
	Ownership
>
{
	using
	type
	=
	fcppt::mpl::list::append<
		typename
		sge::sprite::detail::primitives::texture_ptr<
			Choices,
			TextureLevels,
			Ownership
		>::type,
		typename
		sge::sprite::detail::primitives::texture_repetition<
			Choices
		>::type
	>;
};

template<
	typename Choices,
	typename TextureLevels,
	sge::sprite::config::texture_ownership Ownership
>
struct texture<
	Choices,
	TextureLevels,
	sge::sprite::config::texture_coordinates::automatic,
	Ownership
>
{
	using
	type
	=
	typename
	sge::sprite::detail::primitives::texture_ptr<
		Choices,
		TextureLevels,
		Ownership
	>::type;
};

}
}
}
}

#endif
