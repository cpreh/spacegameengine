//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_SET_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_SET_CENTER_HPP_INCLUDED

#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/roles/center.hpp>
#include <sge/sprite/roles/pos_or_center.hpp>
#include <sge/sprite/types/center.hpp>
#include <sge/sprite/types/pos_or_center.hpp>
#include <fcppt/record/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename Elements
>
inline
typename
std::enable_if<
	Choices::pos_choice::option::value
	==
	sge::sprite::config::pos_option::center
	,
	void
>::type
set_center(
	Elements &_elements,
	sge::sprite::types::center<
		typename
		Choices::type_choices
	> const _center

)
{
	fcppt::record::set<
		sge::sprite::roles::center
	>(
		_elements,
		_center.get()
	);
}

template<
	typename Choices,
	typename Elements
>
inline
typename
std::enable_if<
	Choices::pos_choice::option::value
	==
	sge::sprite::config::pos_option::pos_or_center
	,
	void
>::type
set_center(
	Elements &_elements,
	sge::sprite::types::center<
		typename
		Choices::type_choices
	> const _center
)
{
	fcppt::record::set<
		sge::sprite::roles::pos_or_center
	>(
		_elements,
		sge::sprite::types::pos_or_center<
			typename
			Choices::type_choices
		>(
			_center
		)
	);
}

}
}
}

#endif
