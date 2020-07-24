//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED

#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/detail/symbol.hpp>


namespace sge
{
namespace rucksack
{

class axis_policy2
{
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	axis_policy2(
		sge::rucksack::axis_policy const &,
		sge::rucksack::axis_policy const &
	);

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	x() const;

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	y() const;

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy const &
	operator[](
		sge::rucksack::axis
	) const;
private:
	sge::rucksack::axis_policy
		x_,
		y_;
};

}
}

#endif
