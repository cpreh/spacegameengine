//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_IMPL_UPDATE_AXIS_HPP_INCLUDED
#define SGE_RUCKSACK_IMPL_UPDATE_AXIS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/enum/size.hpp>


namespace sge
{
namespace rucksack
{
namespace impl
{

template<
	typename Ret
>
[[nodiscard]]
Ret
update_axis(
	Ret _result,
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _scalar
)
{
	static_assert(
		Ret::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value
	);

	_result.get_unsafe(
		sge::rucksack::axis_to_index(
			_axis
		)
	) =
		_scalar;

	return
		_result;
}

}
}
}

#endif
