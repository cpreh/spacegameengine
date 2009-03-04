#ifndef SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED

#include "../space_fwd.hpp"
#include "../world_fwd.hpp"
#include "../body.hpp"
#include "../geom.hpp"
#include "../plane_joint.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/sattelite.hpp>
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
		collision::sattelite_ptr,
		space &,
		world &,
		point const &center,
		point const &speed,
		dReal radius);

	void center(collision::point const &);
	collision::point const center() const;
	void speed(collision::point const &);
	collision::point const speed() const;
private:
	body body_;
	geom geom_;
	plane_joint joint_;
	collision::sattelite_ptr sattelite_;
};
}
}
}

#endif
