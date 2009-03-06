#ifndef SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED

#include "../space_fwd.hpp"
#include "../world_wrapper_fwd.hpp"
#include "../body.hpp"
#include "../geom.hpp"
#include "../plane_joint.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
namespace objects
{
class circle : public collision::objects::circle
{
public:
	circle(
		collision::satellite_ptr,
		space &,
		world_wrapper &,
		point const &center,
		point const &speed,
		dReal radius);

	~circle();

	void center(collision::point const &);
	collision::point const center() const;
	void speed(collision::point const &);
	collision::point const speed() const;
private:
	body body_;
	geom geom_;
	plane_joint joint_;
	collision::satellite_ptr satellite_;
};
}
}
}

#endif
