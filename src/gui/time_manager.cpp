#include <sge/gui/detail/time_manager.hpp>
#include <sge/gui/timer/object.hpp>

sge::gui::timer::object_ptr const sge::gui::detail::time_manager::add(
	time::resolution const &r,
	timer::callback const cb)
{
	timer::object_ptr p(new timer::object(r,cb));
	timers.push_back(p.boost_ptr());
	return p;
}

void sge::gui::detail::time_manager::draw()
{
	for (timer_container::iterator i = timers.begin(); i != timers.end();)
	{
		if ((*i).expired())
		{
			i = timers.erase(i);
			continue;
		}
		(*i).lock()->update();
	}
}
