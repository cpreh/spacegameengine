#ifndef SGE_ODE_BODY_HPP_INCLUDED
#define SGE_ODE_BODY_HPP_INCLUDED

#include "world_fwd.hpp"
#include "transformer_fwd.hpp"
#include "group_id.hpp"
#include <sge/collision/body.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
class body
:
	public sge::collision::body
{
public:
	body(
		world &,
		transformer const &,
		dWorldID,
		collision::satellite_ptr,
		collision::point const &,
		collision::point const &);
	collision::point const position() const;
	void position(
		collision::point const &);
	collision::point const linear_velocity() const;
	void linear_velocity(
		collision::point const &);
	void add(
		collision::shapes::base_ptr);
	bool is_active();
	void is_active(
		bool);
	~body();
private:
	// world needs to access the satellite in its collision function
	friend class world;
	
	world &world_;
	transformer const &transformer_;
	dBodyID body_;
	collision::satellite_ptr satellite_;
	
	static void moved(
		dBodyID);
};
}
}

#endif