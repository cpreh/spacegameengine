//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_POS_HPP_INCLUDED

#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/pos_or_center.hpp>
#include <sge/sprite/types/pos_or_center_fwd.hpp>
#include <sge/sprite/types/vector_fwd.hpp>
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
	typename Choices,
	sge::sprite::config::pos_option
>
struct pos;

template<
	typename Choices
>
struct pos<
	Choices,
	sge::sprite::config::pos_option::pos
>
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::pos,
			sge::sprite::types::vector<
				typename
				Choices::type_choices
			>
		>
	>
	type;
};

template<
	typename Choices
>
struct pos<
	Choices,
	sge::sprite::config::pos_option::center
>
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::center,
			sge::sprite::types::vector<
				typename
				Choices::type_choices
			>
		>
	>
	type;
};

template<
	typename Choices
>
struct pos<
	Choices,
	sge::sprite::config::pos_option::pos_or_center
>
{
	typedef
	metal::list<
		fcppt::record::element<
			sge::sprite::roles::pos_or_center,
			sge::sprite::types::pos_or_center<
				typename
				Choices::type_choices
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
