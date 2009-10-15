#ifndef SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED

#include <sge/collision/point.hpp>
#include <sge/collision/solidity.hpp>
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
	SGE_SYMBOL virtual ~base();
	
	// FIXME: technically you should have getters and setters for:
	// solidity
	// position
	// but I was way too lazy for that
};
}
}
}

#endif
