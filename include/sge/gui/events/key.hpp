#ifndef SGE_GUI_EVENTS_KEY_HPP_INCLUDED
#define SGE_GUI_EVENTS_KEY_HPP_INCLUDED

#include "../../input/key_pair.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace events
{
class key
{
	public:
	SGE_SYMBOL key(input::key_pair const &);
	input::key_pair const value() const { return kp; }
	private:
	input::key_pair const kp;
};
}
}
}

#endif
