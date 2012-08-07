#ifndef SGE_RUCKSACK_ASPECT_HPP_INCLUDED
#define SGE_RUCKSACK_ASPECT_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/symbol.hpp>

namespace sge
{
namespace rucksack
{
class aspect
{
public:
	SGE_RUCKSACK_SYMBOL
	aspect(
		sge::rucksack::scalar,
		sge::rucksack::scalar);

	SGE_RUCKSACK_SYMBOL sge::rucksack::scalar
	x() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::scalar
	y() const;
private:
	sge::rucksack::scalar x_,y_;
};
}
}

#endif
