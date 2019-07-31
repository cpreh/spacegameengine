//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_ACCESS_AXIS_HPP_INCLUDED
#define SGE_RUCKSACK_ACCESS_AXIS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <fcppt/enum/size.hpp>


namespace sge
{
namespace rucksack
{

template<
	typename Value
>
typename
Value::value_type
access_axis(
	Value const &_value,
	sge::rucksack::axis const _axis
)
{
	static_assert(
		Value::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value,
		""
	);

	return
		_value.get_unsafe(
			sge::rucksack::axis_to_index(
				_axis
			)
		);
}

}
}

#endif
