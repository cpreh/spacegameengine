#ifndef SGE_BULLET_BODY_HPP_INCLUDED
#define SGE_BULLET_BODY_HPP_INCLUDED

#include "point.hpp"
#include "world_fwd.hpp"
#include "shapes/base_fwd.hpp"
#include <sge/collision/satellite_fwd.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/shapes/container.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>

namespace sge
{
namespace bullet
{
class body
:
	public collision::body
{
public:
	body(
		world &,
		collision::shapes::container const &,
		point const &position,
		point const &linear_velocity);
	
	collision::point const 
	position() const;
	
	void 
	position(
		collision::point const &);
		
	collision::point const 
	linear_velocity() const;
	
	void 
	linear_velocity(
		collision::point const &);
	
	void 
	add_shape(
		collision::shapes::base_ptr);
	
	// Is called by shapes::bases destructor
	void
	remove_shape(
		shapes::base &);
	
	~body();
private:
	typedef 
	std::vector<shapes::base_ptr> 
	shape_container;
	
	world &world_;
	shape_container shapes_;
	point position_;
	point linear_velocity_;
	unsigned solid_shapes_;
};
}
}

#endif
