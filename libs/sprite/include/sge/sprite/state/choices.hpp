//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_STATE_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices_fwd.hpp>
#include <fcppt/mpl/list/object_concept.hpp>


namespace sge::sprite::state
{

template<
	fcppt::mpl::list::object_concept OptionalElements
>
struct choices
{
	using
	optional_elements
	=
	OptionalElements;
};

}

#endif
