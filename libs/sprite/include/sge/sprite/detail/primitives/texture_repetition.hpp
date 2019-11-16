//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REPETITION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_REPETITION_HPP_INCLUDED

#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/types/repetition.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices
>
struct texture_repetition
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::repetition,
			sge::sprite::types::repetition<
				typename Choices::type_choices
			>
		>
	>
	type;
};

}
}
}
}

#endif
