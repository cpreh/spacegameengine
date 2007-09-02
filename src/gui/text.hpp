/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_TEXT_HPP_INCLUDED
#define SGE_GUI_TEXT_HPP_INCLUDED

#include <string>
#include <vector>

#include <boost/smart_ptr.hpp>

#include "../texture/manager.hpp"

#include "color.hpp"
#include "types.hpp"

namespace sge {
namespace gui {

class text {
	friend class gui_text_drawer;
private:
	dim2 size_;
	boost::scoped_array<color::channel_t> data;
	sge::string                 glyphs;
	std::vector<sge::gui::rect> glyphpositions;
public:
	text();
	inline const dim2 &size() { return size_; }

private:
	void resize(const dim2 &newsize);
};

}
}

#endif // SGE_GUI_TEXT_HPP_INCLUDED
