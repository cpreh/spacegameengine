#ifndef SGE_GUI_DETAIL_MANAGERS_TIME_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_TIME_HPP_INCLUDED

#include <sge/gui/detail/submanager.hpp>
#include <sge/time/resolution.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/weak_ptr.hpp>
#include <vector>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class time : public submanager
{
	public:
	timer::object_ptr const add(
		sge::time::resolution const &,
		timer::callback);
	void draw();
	private:
	using submanager::add;
	typedef weak_ptr<timer::object> weak_object_ptr;
	typedef std::vector<weak_object_ptr> timer_container;
	timer_container timers;
};
}
}
}
}

#endif
