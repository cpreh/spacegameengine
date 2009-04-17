#ifndef SGE_GUI_KEY_HANDLING_HPP_INCLUDED
#define SGE_GUI_KEY_HANDLING_HPP_INCLUDED

// This is the return value of the process(key) event and determines if the gui
// should process the key after the widget got it. For example, a widget could
// decide to completely ignore the key (like a button ignores the "tab" key, so
// the manager uses it to cycle the keyboard focus), it could process the key
// and don't let the manager do anything with it (widgets::edit probably wants
// to process the tab key and display a tab character), or it could process the
// key and then hand it over to the manager.

namespace sge
{
namespace gui
{
namespace key_handling
{
enum type 
{ 
	process,
	ignore 
};
}
}
}

#endif
