#ifndef SGE_RUCKSACK_DIM_HPP_INCLUDED
#define SGE_RUCKSACK_DIM_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <fcppt/math/dim/static.hpp>

namespace sge
{
namespace rucksack
{
typedef
fcppt::math::dim::static_<sge::rucksack::scalar,2>::type
dim;
}
}

#endif
