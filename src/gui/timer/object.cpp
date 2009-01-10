#include <sge/gui/timer/object.hpp>

sge::gui::timer::object::object(
	time::resolution const &r,
	timer::callback const cb)
	: t(r),
	  cb(cb)
{
}

void sge::gui::timer::object::update()
{
	if (t.update_b())
		cb();
}
