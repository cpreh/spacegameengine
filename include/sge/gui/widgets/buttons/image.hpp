/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_WIDGETS_BUTTONS_IMAGE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_IMAGE_HPP_INCLUDED

#include <sge/gui/widgets/buttons/base.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{
class SGE_CLASS_SYMBOL image : public base
{
public:
	SGE_GUI_SYMBOL image(
		parent_data const &,
		parameters,
		const_image_ptr normal,
		const_image_ptr hover,
		const_image_ptr keyboard,
		const_image_ptr hover_keyboard);

	// TODO: move to cpp file
	const_image_ptr normal() const { return normal_; }
	const_image_ptr hover() const { return hover_; }
	const_image_ptr keyboard() const { return keyboard_; }
	const_image_ptr hover_keyboard() const { return hover_keyboard_; }
private:
	const_image_ptr normal_,hover_,keyboard_,hover_keyboard_;
};
}
}
}
}

#endif
