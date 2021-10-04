//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_COMPARE_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/detail/textures.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::compare
{

struct textures
{
	template<
		typename Choices
	>
	using
	is_trivial
	=
	std::false_type;

	using
	result_type
	=
	bool;

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
			sge::sprite::compare::detail::textures<
				sge::sprite::detail::config::texture_levels<
					Choices
				>::value
			>::execute(
				_left,
				_right
			);
	}
};

}

#endif
