#ifndef SGE_MAD_TIMER_HPP_INCLUDED
#define SGE_MAD_TIMER_HPP_INCLUDED

#include <mad.h>

namespace sge
{
namespace mad
{
class timer
{
	public:
	timer();
	mad_timer_t &madtimer() { return timer_; }
	mad_timer_t const &madtimer() const { return timer_; }

	private:
	mad_timer_t timer_;
};
}
}

#endif
