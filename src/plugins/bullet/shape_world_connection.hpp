#ifndef SGE_BULLET_SHAPE_WORLD_CONNECTION_HPP_INCLUDED
#define SGE_BULLET_SHAPE_WORLD_CONNECTION_HPP_INCLUDED

#include "shapes/base_fwd.hpp"
#include "group_id.hpp"
#include "world_fwd.hpp"

class btRigidBody;

namespace sge
{
namespace bullet
{
class shape_world_connection
{
public:
	explicit
	shape_world_connection(
		shapes::base &,
		world &);
	
	bool
	in_world() const;
	
	group_id &
	mask();
	
	group_id &
	group();
	
	void
	insert();
	
	void 
	remove();
	
	~shape_world_connection();
private:
	shapes::base &shape_;
	world &world_;
	
	bool in_world_;
	
	group_id 
		queued_mask_,
		queued_group_;
};
}
}

#endif
