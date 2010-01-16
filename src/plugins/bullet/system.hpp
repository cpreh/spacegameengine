#ifndef SGE_BULLET_SYSTEM_HPP_INCLUDED
#define SGE_BULLET_SYSTEM_HPP_INCLUDED

#include <sge/collision/system.hpp>

class btManifoldPoint;
class btCollisionObject;

namespace sge
{
namespace bullet
{
class system
:
	public sge::collision::system
{
public:
	system();
	
	collision::world_ptr const
	create_world(
		collision::optional_box const &,
		collision::constraint::type);
private:
	static bool
	collision_begin(
		btManifoldPoint& cp,
		btCollisionObject const *colObj0,
		int partId0,
		int index0,
		btCollisionObject const *colObj1,
		int partId1,
		int index1);
	
	static bool
	collision_processed(
		btManifoldPoint &,
		void* body0,
		void* body1);
	
	static bool
	collision_end(
		void*);
};
}
}

#endif