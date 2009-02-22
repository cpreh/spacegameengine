#ifndef SGE_GUI_TIMER_OBJECT_HPP_INCLUDED
#define SGE_GUI_TIMER_OBJECT_HPP_INCLUDED

#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/timer/callback.hpp>
#include <sge/time/timer.hpp>
#include <sge/time/resolution.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace gui
{
namespace timer
{
class object
{
	public:
	object(time::resolution const &,timer::callback);
	void update();
	private:
	time::timer t;
	timer::callback cb;
};
}
}
}

#endif
