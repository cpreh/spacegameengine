#ifndef SGE_GUI_EVENTS_KEY_HPP_INCLUDED
#define SGE_GUI_EVENTS_KEY_HPP_INCLUDED

#include "../../input/key_pair.hpp"
#include "../../input/modifier/states.hpp"
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
	SGE_SYMBOL key(input::key_pair const &,input::modifier::states const &,bool);
	input::key_pair const value() const { return kp; }
	input::modifier::states const modifiers() const { return s; }
	bool repeated() const { return repeated_; };
	private:
	input::key_pair const kp;
	input::modifier::states const s;
	bool repeated_;
};
}
}
}

#endif
