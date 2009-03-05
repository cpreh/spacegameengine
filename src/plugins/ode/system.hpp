#ifndef SGE_ODE_SYSTEM_HPP_INCLUDED
#define SGE_ODE_SYSTEM_HPP_INCLUDED

#include <sge/collision/system.hpp>

namespace sge
{
namespace ode
{
class system : public collision::system
{
public:
	system();
	sge::collision::world_ptr const create_world(
		boost::optional<collision::rect> const &);
	~system();
};
}
}

#endif
