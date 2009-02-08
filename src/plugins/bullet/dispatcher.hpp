#ifndef SGE_BULLET_DISPATCHER_HPP_INCLUDED
#define SGE_BULLET_DISPATCHER_HPP_INCLUDED

#include <bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <sge/collision/callbacks.hpp>

class btCollisionConfiguration;
class btBroadphasePair;
class btDispatcherInfo;

namespace sge
{
namespace bullet
{
class dispatcher : public btCollisionDispatcher
{
	public:
	dispatcher(
		btCollisionConfiguration &,
		collision::callback_signal &collision);
	private:
	collision::callback_signal &collision;

	static void near_callback(
		btBroadphasePair&,
		btCollisionDispatcher&, 
		btDispatcherInfo const &);
};
}
}

#endif
