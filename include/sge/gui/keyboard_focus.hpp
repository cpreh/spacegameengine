#ifndef SGE_GUI_KEYBOARD_FOCUS_HPP_INCLUDED
#define SGE_GUI_KEYBOARD_FOCUS_HPP_INCLUDED

// This determines if a widget wants to receive the keyboard focus. A label,
// for example, is probably not interested in the keyboard focus, a button might be. 

namespace sge
{
namespace gui
{
namespace keyboard_focus
{
enum type 
{ 
	ignore,
	receive
};
}
}
}

#endif
