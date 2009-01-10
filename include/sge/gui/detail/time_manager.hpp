#ifndef SGE_GUI_DETAIL_TIME_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_TIME_MANAGER_HPP_INCLUDED

#include "../../time/resolution.hpp"
#include "../timer/callback.hpp"
#include "../timer/fwd.hpp"
#include <boost/weak_ptr.hpp>
#include <vector>

namespace sge
{
namespace gui
{
namespace detail
{
class time_manager
{
	public:
	timer::object_ptr const add(
		time::resolution const &,
		timer::callback);
	void draw();
	private:
	typedef boost::weak_ptr<timer::object> weak_object_ptr;
	typedef std::vector<weak_object_ptr> timer_container;
	timer_container timers;
};
}
}
}

#endif
