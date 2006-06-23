#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

namespace sge
{
namespace gui
{

class skin {
public:
	typedef const char* const name_type;
	static name_type button_name,
	       button_pressed_name,
	       button_hover_name,
	       textedit_name,
	       cursor_name,
	       cursor_pressed_name,
	       textcursor_name,
	       inner_scrollbar_name,
	       left_scrollbutton_name,
	       right_scrollbutton_name,
	       up_scrollbutton_name,
	       down_scrollbutton_name,
	       scrollbar_name,
	       list_background_name,
	       statictext_name,
	       checkbox_name,
	       clickbox_round_pressed_name,
	       clickbox_round_name,
	       clickbox_quad_pressed_name,
	       clickbox_quad_name;
};

}
}

#endif
