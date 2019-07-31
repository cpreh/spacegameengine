//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_RANGE_PART_VECTOR_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_VECTOR_HPP_INCLUDED

#include <sge/sprite/render/range_part_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices
>
using range_part_vector
=
std::vector<
	sge::sprite::render::range_part<
		Choices
	>
>;

}
}
}

#endif
