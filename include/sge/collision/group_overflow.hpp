#ifndef SGE_COLLISION_GROUP_OVERFLOW_HPP_INCLUDED
#define SGE_COLLISION_GROUP_OVERFLOW_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL group_overflow
:
	public exception
{
public:
	SGE_SYMBOL group_overflow();
};
}
}

#endif