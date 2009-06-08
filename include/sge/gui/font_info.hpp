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


#ifndef SGE_GUI_FONT_INFO_HPP_INCLUDED
#define SGE_GUI_FONT_INFO_HPP_INCLUDED

#include <sge/gui/export.hpp>
#include <sge/gui/color.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/variant/object_impl.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL font_info
{
public:
	SGE_GUI_SYMBOL font_info(
		font::metrics_ptr,
		sge::gui::color const &);
	
	SGE_GUI_SYMBOL font::metrics_ptr const metrics() const;
	SGE_GUI_SYMBOL sge::gui::color const color() const;
private:
	font::metrics_ptr metrics_;
	sge::gui::color color_;
};
}
}

#endif
