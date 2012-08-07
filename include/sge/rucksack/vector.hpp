#ifndef SGE_RUCKSACK_VECTOR_HPP_INCLUDED
#define SGE_RUCKSACK_VECTOR_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sge
{
namespace rucksack
{
typedef
fcppt::math::vector::static_<sge::rucksack::scalar,2>::type
vector;
}
}

#endif
