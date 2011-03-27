#ifndef SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/body/position_change.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/position_change_fn.hpp>
#include <sge/projectile/body/rotation_change.hpp>
#include <sge/projectile/body/rotation_change_fn.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/parameters_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <bullet/LinearMath/btMotionState.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <bullet/BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <bullet/LinearMath/btTransform.h>

namespace sge
{
namespace projectile
{
namespace body
{
class SGE_CLASS_SYMBOL object
:
	public btMotionState
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_SYMBOL explicit
	object(
		parameters const &);
	
	SGE_PROJECTILE_SYMBOL vector2 const 
	position() const;
	
	SGE_PROJECTILE_SYMBOL void 
	position(
		vector2 const &);

	SGE_PROJECTILE_SYMBOL vector2 const 
	linear_velocity() const;
	
	SGE_PROJECTILE_SYMBOL void 
	linear_velocity(
		vector2 const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::shape::shared_base_ptr const
	shape() const;
		
	SGE_PROJECTILE_SYMBOL scalar
	rotation() const;
	
	SGE_PROJECTILE_SYMBOL void 
	rotation(
		scalar);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	position_change(
		sge::projectile::body::position_change const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	SGE_PROJECTILE_SYMBOL rotation_change(
		sge::projectile::body::rotation_change const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::body::user_data const &
	user_data() const;
		
	SGE_PROJECTILE_SYMBOL ~object();
private:
	friend class sge::projectile::group::object;

	btDynamicsWorld &world_;
	btTransform transformation_;
	fcppt::signal::object<position_change_fn> position_change_;
	fcppt::signal::object<rotation_change_fn> rotation_change_;
	shape::shared_base_ptr shape_;
	btRigidBody body_;
	sge::projectile::body::user_data user_data_;

	// @override
	void	
	getWorldTransform(
		btTransform &) const;

	// @override
	void	
	setWorldTransform(
		btTransform const &);
};
}
}
}

#endif
