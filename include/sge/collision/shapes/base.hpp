#ifndef SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED

#include <sge/collision/point.hpp>
#include <sge/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class SGE_CLASS_SYMBOL base
{
SGE_NONCOPYABLE(base)
protected:
	base();
public:
	virtual void 
	position(
		point const &) = 0;

	virtual void
	is_solid(
			bool) = 0;

	SGE_SYMBOL virtual ~base();
};
}
}
}

#endif
