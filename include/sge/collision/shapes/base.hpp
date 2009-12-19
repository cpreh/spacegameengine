#ifndef SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED
#define SGE_COLLISION_SHAPES_BASE_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace collision
{
namespace shapes
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(base)
protected:
	base();
public:
	SGE_SYMBOL virtual ~base();
};
}
}
}

#endif