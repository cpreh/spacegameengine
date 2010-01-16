#ifndef SGE_BULLET_CONVERT_TO_BULLET_HPP_INCLUDED
#define SGE_BULLET_CONVERT_TO_BULLET_HPP_INCLUDED

#include "../point.hpp"
#include "../dim.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <LinearMath/btVector3.h>

namespace sge
{
namespace bullet
{
namespace convert
{
inline btVector3 const 
to_bullet(
	point const &p)
{
	return
		btVector3(
			p.x(),
			p.y(),
			p.z());
}

inline btVector3 const 
to_bullet(
	dim const &p)
{
	return
		btVector3(
			p.w(),
			p.h(),
			p.d());
}
}
}
}

#endif
