//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/compare/textures.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{

struct default_
{
	using
	result_type
	=
	bool;

	template<
		typename Choices
	>
	using
	is_trivial
	=
	std::negation<
		sge::sprite::detail::config::has_texture<
			Choices
		>
	>;

	template<
		typename Choices
	>
	inline
	std::enable_if_t<
		sge::sprite::detail::config::has_texture<
			Choices
		>::value,
		result_type
	>
	operator()(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	) const
	{
		return
			sge::sprite::compare::textures()(
				_left,
				_right
			);
	}

	template<
		typename Choices
	>
	inline
	std::enable_if_t<
		fcppt::not_(
			sge::sprite::detail::config::has_texture<
				Choices
			>::value
		),
		result_type
	>
	operator()(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	) const
	{
		return
			sge::sprite::compare::nothing()(
				_left,
				_right
			);
	}
};

}
}
}

#endif
