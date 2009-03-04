#ifndef SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_ODE_OBJECTS_CIRCLE_HPP_INCLUDED

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
		sattelite_ptr,
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
	sattelite_ptr sattelite_;
};
}
}
}

#endif
