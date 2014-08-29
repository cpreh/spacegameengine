#ifndef SGE_SRC_RUCKSACK_MAKE_COMPONENTS_HPP_INCLUDED
#define SGE_SRC_RUCKSACK_MAKE_COMPONENTS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{

template<
	typename Ret
>
Ret
make_components(
	std::pair<
		sge::rucksack::axis,
		sge::rucksack::scalar
	> const _pair1,
	std::pair<
		sge::rucksack::axis,
		sge::rucksack::scalar
	> const _pair2
)
{
	Ret ret{
		fcppt::no_init()
	};

	auto const assign(
		[
			&ret
		](
			std::pair<
				sge::rucksack::axis,
				sge::rucksack::scalar
			> const _pair
		)
		{
			ret[
				sge::rucksack::axis_to_index(
					_pair.first
				)
			] =
				_pair.second;
		}
	);

	assign(
		_pair1
	);

	assign(
		_pair2
	);

	return
		ret;
}

}
}

#endif
