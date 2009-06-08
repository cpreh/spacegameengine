/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED
#define SGE_GUI_WIDGETS_LABEL_HPP_INCLUDED

#include <sge/gui/widgets/base.hpp>
#include <sge/gui/widgets/optional_dim.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/font_info.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/align_v.hpp>
#include <sge/optional.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL label : public base
{
public:
	SGE_GUI_SYMBOL label(
		parent_data const &,
		parameters,
		string const &,
		sge::font::align_h::type = sge::font::align_h::left,
		sge::font::align_v::type = sge::font::align_v::top,
		optional_dim const &static_size = optional_dim());
	
	SGE_GUI_SYMBOL sge::gui::color const color() const;
	SGE_GUI_SYMBOL string const text() const;
	SGE_GUI_SYMBOL sge::font::align_h::type align_h() const;
	SGE_GUI_SYMBOL sge::font::align_v::type align_v() const;
	SGE_GUI_SYMBOL void text(string const &_text);
	SGE_GUI_SYMBOL optional_dim const &static_size() const;
	private:
	string text_;
	sge::font::align_h::type align_h_;
	sge::font::align_v::type align_v_;
	optional_dim static_size_;
	sge::gui::color color_;
};
}
}
}

#endif
