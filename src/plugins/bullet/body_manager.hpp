#ifndef SGE_BULLET_BODY_MANAGER_HPP_INCLUDED
#define SGE_BULLET_BODY_MANAGER_HPP_INCLUDED

#include "world_fwd.hpp"
#include "collision_proxy.hpp"
#include <sge/collision/shape_callback.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <map>

class btRigidBody;
class btManifoldPoint;

namespace sge
{
namespace bullet
{
class body_manager
{
public:
	// the body manager has to know the world because collision_proxy gets it
	explicit 
	body_manager(
		world &);
	
	collision_proxy const &
	begin(
		btManifoldPoint &,
		shapes::base &,
		shapes::base &);
	
	void
	end(
		shapes::base &,
		shapes::base &);
	
	fcppt::signal::auto_connection
	register_begin(
		collision::shape_callback const &);
		
	fcppt::signal::auto_connection
	register_end(
		collision::shape_callback const &);
		
	fcppt::signal::auto_connection
	register_solid(
		collision::shape_callback const &);
private:
	typedef 
	unsigned
	size_type;
	
	// no sge::container::map here because it lacks the pair<iterator,bool>::insert method
	typedef
	std::map
	<
		collision_proxy,
		size_type
	>
	pair_map;
	
	fcppt::signal::object<collision::shape_callback_fn> 
		begin_callback_,
		end_callback_,
		solid_callback_;
	world &world_;
	pair_map pairs_;
};
}
}

#endif
