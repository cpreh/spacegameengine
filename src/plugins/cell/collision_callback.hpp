#ifndef SGE_CELL_COLLISION_CALLBACK_HPP_INCLUDED
#define SGE_CELL_COLLISION_CALLBACK_HPP_INCLUDED

#include <boost/function.hpp>

namespace sge
{
namespace cell
{

class circle;

typedef boost::function<
	void (
		circle &,
		circle &
	)
> collision_callback;

}
}

#endif
