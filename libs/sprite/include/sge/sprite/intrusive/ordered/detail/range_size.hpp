//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_SIZE_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_ORDERED_DETAIL_RANGE_SIZE_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/intrusive/ordered/detail/map.hpp>
#include <fcppt/algorithm/fold.hpp>


namespace sge::sprite::intrusive::ordered::detail
{

template<
	typename Order,
	typename Choices
>
inline
sge::sprite::count
range_size(
	sge::sprite::intrusive::ordered::detail::map<
		Order,
		Choices
	> const &_ordered_map
)
{
	return
		fcppt::algorithm::fold(
			_ordered_map,
			sge::sprite::count{
				0U
			},
			[](
				auto const &_element,
				sge::sprite::count const _value
			)
			{
				return
					_value
					+
					_element.second->range().size();
			}
		);
}

}

#endif
