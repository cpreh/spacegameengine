#ifndef SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED
#define SGE_BULLET_OBJECTS_CIRCLE_HPP_INCLUDED

#include "../object.hpp"

namespace sge
{
namespace bullet
{
namespace objects
{
class circle : public object
{
	public:
	circle(
		system &,
		collision::sattelite_ptr,
		collision::unit radius);
};
}
}
}

#endif
