#ifndef SGE_CELL_REGISTER_CALLBACK_HPP_INCLUDED
#define SGE_CELL_REGISTER_CALLBACK_HPP_INCLUDED

#include "circle_list.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace cell
{

class circle;

typedef boost::function<
	circle_list::iterator (circle &)
> register_callback;

}
}

#endif
