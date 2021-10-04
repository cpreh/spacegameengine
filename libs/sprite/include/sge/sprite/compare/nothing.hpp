//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_COMPARE_NOTHING_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_NOTHING_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::compare
{

struct nothing
{
	template<
		typename Choices
	>
	using
	is_trivial
	=
	std::true_type;

	template<
		typename Choices
	>
	inline
	bool
	operator()(
		sge::sprite::object<
			Choices
		> const &,
		sge::sprite::object<
			Choices
		> const &
	) const
	{
		return
			false;
	}
};

}

#endif
