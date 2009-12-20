#ifndef SGE_COLLISION_GROUP_HPP_INCLUDED
#define SGE_COLLISION_GROUP_HPP_INCLUDED

#include <sge/collision/group_fwd.hpp>
#include <sge/collision/body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL group
{
	FCPPT_NONCOPYABLE(group)
protected:
	SGE_SYMBOL group();
public:
	virtual void add(
		body_ptr) = 0;
	SGE_SYMBOL virtual ~group();
};
}
}

#endif
