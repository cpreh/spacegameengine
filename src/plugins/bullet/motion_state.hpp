#ifndef SGE_BULLET_MOTION_STATE_HPP_INCLUDED
#define SGE_BULLET_MOTION_STATE_HPP_INCLUDED

#include "point.hpp"
#include "body_fwd.hpp"
#include <sge/collision/satellite_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <LinearMath/btMotionState.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

class btRigidBody;

namespace sge
{
namespace bullet
{
class motion_state
:
	public btMotionState
{
public:
	motion_state(
		collision::satellite &,
		btRigidBody &,
		point &relative_position);
	
	void 
	getWorldTransform(
		btTransform&) const;

	void 
	setWorldTransform(
		btTransform const &);
	
	point const 
	position() const;
	
	void 
	position(
		point const &);
	
	void
	meta_body(
		body &);
	
	void 
	is_position_changer(
		bool);
	
	bool
	is_position_changer() const;
	
	~motion_state();
private:
	collision::satellite &satellite_;
	btRigidBody &body_;
	point &relative_position_;
	point position_;
	body *meta_body_;
	bool is_position_changer_;
};
}
}

#endif
