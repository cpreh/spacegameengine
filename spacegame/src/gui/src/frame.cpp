#include "../frame.hpp"

sge::gui::frame::frame(manager& m, element* const parent, const point pos, const dim sz, const std::string& my_texture, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,my_texture,visible,enabled)
{}
