#ifndef SGE_CELL_UNREGISTER_CALLBACK_HPP_INCLUDED
#define SGE_CELL_UNREGISTER_CALLBACK_HPP_INCLUDED

#include "circle_list.hpp"
#include <boost/function.hpp>

namespace sge
{
namespace cell
{

typedef boost::function<
	void (
		circle_list::iterator
	)
> unregister_callback;

}
}

#endif
