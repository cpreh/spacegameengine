#include <fstream>
#include "../skin.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#define DEFINE_SKIN_NAME(x) sge::gui::skin::name_type sge::gui::skin:: x##_name = #x;

DEFINE_SKIN_NAME(button)
DEFINE_SKIN_NAME(button_pressed)
DEFINE_SKIN_NAME(button_hover)
DEFINE_SKIN_NAME(textedit)
DEFINE_SKIN_NAME(cursor)
DEFINE_SKIN_NAME(cursor_pressed)
DEFINE_SKIN_NAME(textcursor)
DEFINE_SKIN_NAME(scrollbar)
DEFINE_SKIN_NAME(inner_scrollbar)
DEFINE_SKIN_NAME(left_scrollbutton)
DEFINE_SKIN_NAME(right_scrollbutton)
DEFINE_SKIN_NAME(up_scrollbutton)
DEFINE_SKIN_NAME(down_scrollbutton)
DEFINE_SKIN_NAME(list_background)
DEFINE_SKIN_NAME(statictext)
DEFINE_SKIN_NAME(checkbox)
DEFINE_SKIN_NAME(clickbox_round_pressed)
DEFINE_SKIN_NAME(clickbox_round)
DEFINE_SKIN_NAME(clickbox_quad_pressed)
DEFINE_SKIN_NAME(clickbox_quad)

#undef DEFINE_SKIN_NAME
