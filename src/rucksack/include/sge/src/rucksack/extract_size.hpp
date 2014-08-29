#ifndef SGE_SRC_RUCKSACK_EXTRACT_SIZE_HPP_INCLUDED
#define SGE_SRC_RUCKSACK_EXTRACT_SIZE_HPP_INCLUDED

#include <sge/rucksack/axis_policy_fwd.hpp>
#include <sge/rucksack/scalar.hpp>


namespace sge
{
namespace rucksack
{

sge::rucksack::scalar
extract_size(
	sge::rucksack::axis_policy const &
);

}
}

#endif
