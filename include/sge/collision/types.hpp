#ifndef SGE_COLLISION_TYPES_HPP_INCLUDED
#define SGE_COLLISION_TYPES_HPP_INCLUDED

#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace collision
{
typedef float unit;
typedef math::vector::static_<
	unit,
	3
>::type point;

}
}

#endif
