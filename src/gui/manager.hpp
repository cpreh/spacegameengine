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


#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "canvas.hpp"
#include "cursor.hpp"
#include "widget.hpp"

namespace sge {
namespace gui {

class manager : public widget {
	friend struct input_callback_functor;
public:
	manager();
	manager(sge::gui::dim2);
	~manager();

	manager *top_level_widget() const;
	void resize(dim2 newsize);

	inline cursor_ptr cursor() const { return cursor_; }
	void cursor(cursor_ptr);

protected:
	canvas framebuffer;
	cursor_ptr cursor_;
	sge::virtual_texture_ptr last_texture;

	virtual void input_callback();

public:
	sge::virtual_texture_ptr to_texture(sge::texture_manager &texmgr);
};

}
}

#endif // SGE_GUI_MANAGER_HPP_INCLUDED
