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
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/assert.hpp>

sge::gui::widgets::buttons::image::image(
	parent_data const &_parent,
	parameters _params,
	const_image_ptr _normal,
	const_image_ptr _hover,
	const_image_ptr _keyboard,
	const_image_ptr _hover_keyboard)
:
	base(
		_parent,
		_params
			.size_policy(
				sge::gui::size_policy(
					axis_policy::none,
					axis_policy::none))
				/*
				.size(
					dim(
						static_cast<unit>(normal_->width()),
						static_cast<unit>(normal_->height())))*/),
	normal_(_normal),
	hover_(_hover),
	keyboard_(_keyboard),
	hover_keyboard_(_hover_keyboard)
{
	SGE_ASSERT(
		normal_->size() == hover_->size() && 
		hover_->size() == keyboard_->size() && 
		keyboard_->size() == hover_keyboard_->size());
}
