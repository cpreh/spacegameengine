#include "../overlap_callback.hpp"
#include "../types.hpp"
#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>

sge::bullet::overlap_callback::overlap_callback(
	collision::test_callback const &dispatch)
	: dispatch(dispatch)
{
}

void sge::bullet::overlap_callback::reset(
	collision::test_callback const &_dispatch)
{
	dispatch = _dispatch;
}

bool sge::bullet::overlap_callback::needBroadphaseCollision(
	btBroadphaseProxy * const a,
	btBroadphaseProxy * const b) const
{
	return dispatch(
		*static_cast<collision::sattelite const *>(
			static_cast<body_type *>(a->m_clientObject)->getUserPointer()),
		*static_cast<collision::sattelite const *>(
			static_cast<body_type *>(b->m_clientObject)->getUserPointer())
		);
}
