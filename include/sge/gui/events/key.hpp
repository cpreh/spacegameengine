#ifndef SGE_GUI_EVENTS_KEY_HPP_INCLUDED
#define SGE_GUI_EVENTS_KEY_HPP_INCLUDED

#include <sge/input/key_pair.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/container/map_decl.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class key
{
	public:
	SGE_GUI_SYMBOL key(
		input::key_pair const &,
		input::modifier::states const &,
		bool repeated);
	
	SGE_GUI_SYMBOL input::key_pair const &value() const;
	SGE_GUI_SYMBOL input::modifier::states const &modifiers() const;
	SGE_GUI_SYMBOL bool repeated() const;
	private:
	input::key_pair const kp;
	input::modifier::states const s;
	bool repeated_;
};
}
}
}

#endif
