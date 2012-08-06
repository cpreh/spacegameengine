#ifndef SGE_RUCKSACK_AXIS_POLICY_HPP_INCLUDED
#define SGE_RUCKSACK_AXIS_POLICY_HPP_INCLUDED

#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/symbol.hpp>
#include <fcppt/optional_impl.hpp>


namespace sge
{
namespace rucksack
{
class axis_policy
{
public:
	SGE_RUCKSACK_SYMBOL
	axis_policy(
		sge::rucksack::minimum_size const &,
		sge::rucksack::preferred_size const &,
		sge::rucksack::is_expanding const &);

	SGE_RUCKSACK_SYMBOL sge::rucksack::scalar
	minimum_size() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::optional_scalar
	preferred_size() const;

	SGE_RUCKSACK_SYMBOL bool
	is_expanding() const;
private:
	sge::rucksack::scalar minimum_size_;
	sge::rucksack::optional_scalar preferred_size_;
	bool is_expanding_;
};
}
}

#endif
