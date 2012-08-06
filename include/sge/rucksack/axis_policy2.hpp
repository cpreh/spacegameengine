#ifndef SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY2_HPP_INCLUDED

#include <sge/rucksack/aspect.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/symbol.hpp>
#include <fcppt/math/dim/object_impl.hpp>


namespace sge
{
namespace rucksack
{
class axis_policy2
{
public:
	SGE_RUCKSACK_SYMBOL
	axis_policy2(
		sge::rucksack::axis_policy const &,
		sge::rucksack::axis_policy const &,
		sge::rucksack::aspect const &);

	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy const &
	x() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy const &
	y() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy const &
	operator[](
		sge::rucksack::dim::size_type) const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::aspect const &
	aspect() const;
private:
	sge::rucksack::axis_policy x_,y_;
	sge::rucksack::aspect aspect_;
};
}
}

#endif
