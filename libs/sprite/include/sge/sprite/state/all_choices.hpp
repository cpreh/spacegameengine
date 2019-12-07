//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_ALL_CHOICES_HPP_INCLUDED
#define SGE_SPRITE_STATE_ALL_CHOICES_HPP_INCLUDED

#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/with_blend.hpp>
#include <sge/sprite/state/with_rasterizer.hpp>
#include <sge/sprite/state/with_transform.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

typedef
sge::sprite::state::choices<
	metal::list<
		sge::sprite::state::with_blend,
		sge::sprite::state::with_rasterizer,
		sge::sprite::state::with_transform
	>
>
all_choices;

}
}
}

#endif
