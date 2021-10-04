//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_COMPARE_TEXTURE_LEVEL_EQUAL_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_TEXTURE_LEVEL_EQUAL_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/detail/texture_level_function.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::compare
{

template<
	typename Level,
	typename Choices
>
inline
bool
texture_level_equal(
	sge::sprite::object<
		Choices
	> const &_left,
	sge::sprite::object<
		Choices
	> const &_right
)
{
	static_assert(
		sge::sprite::detail::config::has_texture<
			Choices
		>::value,
		"Sprite choices must have a texture"
	);

	return
		sge::sprite::compare::detail::texture_level_function<
			std::equal_to,
			Level
		>::execute(
			_left,
			_right
		);
}

}

#endif
