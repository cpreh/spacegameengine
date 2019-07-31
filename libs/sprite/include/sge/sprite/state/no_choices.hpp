//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_NO_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_STATE_NO_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

typedef
sge::sprite::state::choices<
	brigand::list<>
>
no_choices;

}
}
}

#endif
