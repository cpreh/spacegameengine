#ifndef SGE_COLLISION_SHAPE_AMBIGUITY_HPP_INCLUDED
#define SGE_COLLISION_SHAPE_AMBIGUITY_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL shape_ambiguity
:
	public exception
{
public:
	SGE_SYMBOL shape_ambiguity();
};
}
}

#endif
