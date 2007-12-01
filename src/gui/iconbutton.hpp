/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_ICONBUTTON_HPP_INCLUDED
#define SGE_GUI_ICONBUTTON_HPP_INCLUDED

#include "button.hpp"

namespace sge {
namespace gui {

class iconbutton : public button {
public:
	iconbutton(widget *parent=0, std::string name="");
	iconbutton(widget *parent, skin::stock_icon::type, std::string name="");
	inline skin::stock_icon::type icon() const { return stockicon; }
	void icon(skin::stock_icon::type);

protected:
	skin::stock_icon::type stockicon;
	void on_update();
};

}
}

#endif // SGE_GUI_ICONBUTTON_HPP_INCLUDED
