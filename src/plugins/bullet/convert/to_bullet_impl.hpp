#ifndef SGE_BULLET_CONVERT_TO_BULLET_IMPL_HPP_INCLUDED
#define SGE_BULLET_CONVERT_TO_BULLET_IMPL_HPP_INCLUDED

#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

btVector3 const sge::bullet::convert::to_bullet(
	point const &p)
{
	return
		btVector3(
			p.x(),
			p.y(),
			p.z());
}

btVector3 const sge::bullet::convert::to_bullet(
	dim const &p)
{
	return
		btVector3(
			p.w(),
			p.h(),
			p.d());
}

#endif