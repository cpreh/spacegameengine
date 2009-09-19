#ifndef SGE_COLLISION_GROUP_HPP_INCLUDED
#define SGE_COLLISION_GROUP_HPP_INCLUDED

#include <sge/collision/group_fwd.hpp>
#include <sge/collision/shapes/base_fwd.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL group
{
//SGE_NONCOPYABLE(group) FIXME: def-ctor, then add noncopyable
public:
	virtual void add(
		shapes::base_ptr) = 0;
	virtual void collides_with(
		group_ptr) = 0;
	SGE_SYMBOL virtual ~group();
};
}
}

#endif