//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_STATE_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename OptionalElements
>
struct choices
{
	typedef OptionalElements optional_elements;

	static_assert(
		metal::is_list<
			OptionalElements
		>::value,
		"OptionalElements must be an mpl sequence"
	);
};

}
}
}

#endif
