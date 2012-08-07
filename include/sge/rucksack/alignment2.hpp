#ifndef SGE_RUCKSACK_ALIGNMENT2_HPP_INCLUDED
#define SGE_RUCKSACK_ALIGNMENT2_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/symbol.hpp>

namespace sge
{
namespace rucksack
{
class alignment2
{
public:
	SGE_RUCKSACK_SYMBOL
	alignment2(
		sge::rucksack::alignment::type,
		sge::rucksack::alignment::type);

	SGE_RUCKSACK_SYMBOL sge::rucksack::alignment::type
	x() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::alignment::type
	y() const;
private:
	sge::rucksack::alignment::type x_,y_;
};
}
}

#endif
