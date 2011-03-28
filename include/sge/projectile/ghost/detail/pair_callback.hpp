#ifndef SGE_PROJECTILE_GHOST_DETAIL_PAIR_CALLBACK_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_DETAIL_PAIR_CALLBACK_HPP_INCLUDED

// The header below isn't self-contained, this is a fix for that
struct btBroadphaseProxy;

#include <bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h>

namespace sge
{
namespace projectile
{
namespace ghost
{
namespace detail
{
class pair_callback
: 
	public btOverlappingPairCallback
{
public:
	btBroadphasePair *
	addOverlappingPair(
		btBroadphaseProxy*,
		btBroadphaseProxy*);

	void*	
	removeOverlappingPair(
		btBroadphaseProxy*,
		btBroadphaseProxy*,
		btDispatcher*);

	void
	removeOverlappingPairsContainingProxy(
		btBroadphaseProxy*,
		btDispatcher*);
};
}
}
}
}

#endif
