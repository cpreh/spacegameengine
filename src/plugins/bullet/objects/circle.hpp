#ifndef SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED

#include <sge/collision/objects/circle.hpp>
#include "../object.hpp"

namespace sge
{
namespace bullet
{
namespace objects
{
class circle : public object, public collision::objects::circle
{
	public:
	circle(
		system &,
		collision::sattelite_ptr,
		collision::unit radius);
	
	void speed(sge::collision::point const &);
	sge::collision::point const speed() const;
	void center(sge::collision::point const &);
	sge::collision::point const center() const;
};
}
}
}

#endif
