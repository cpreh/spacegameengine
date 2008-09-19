#include "timer.hpp"

sge::mad::timer::timer()
{
	mad_timer_reset(&timer_);
}
