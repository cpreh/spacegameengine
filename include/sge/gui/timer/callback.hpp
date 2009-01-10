#ifndef SGE_GUI_TIMER_CALLBACK_HPP_INCLUDED
#define SGE_GUI_TIMER_CALLBACK_HPP_INCLUDED

#include <boost/function.hpp>

namespace sge
{
namespace gui
{
namespace timer
{
typedef boost::function<void ()> callback;
}
}
}

#endif
