#include <sge/gui/detail/managers/time.hpp>
#include <sge/gui/timer/object.hpp>
#include <sge/make_shared_ptr.hpp>

sge::gui::timer::object_ptr const sge::gui::detail::managers::time::add(
	sge::time::resolution const &r,
	timer::callback const cb)
{
	timer::object_ptr const p(
		make_shared_ptr<
			timer::object
		>(
			r,
			cb));
	
	timers.push_back(p);

	return p;
}

void sge::gui::detail::managers::time::update()
{
	for (timer_container::iterator i = timers.begin(); i != timers.end();)
	{
		if ((*i).expired())
		{
			i = timers.erase(i);
			continue;
		}
		(*i).lock()->update();
		++i;
	}
}
