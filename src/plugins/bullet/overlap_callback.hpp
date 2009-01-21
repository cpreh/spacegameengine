#ifndef SGE_BULLET_OVERLAP_CALLBACK_HPP_INCLUDED
#define SGE_BULLET_OVERLAP_CALLBACK_HPP_INCLUDED

#include <sge/collision/callbacks.hpp>
#include <bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.h>

class btBroadphaseProxy;

namespace sge
{
namespace bullet
{
class overlap_callback : public btOverlapFilterCallback
{
	public:
	overlap_callback(collision::test_callback const &);

	bool needBroadphaseCollision(
		btBroadphaseProxy*,
		btBroadphaseProxy*) const;
	
	void reset(collision::test_callback const &);
	private:
	collision::test_callback dispatch;
};
}
}

#endif
