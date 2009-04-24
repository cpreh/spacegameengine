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
#include <sge/gui/widgets/graphics.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/image/object.hpp>
#include <sge/gui/image.hpp>
#include <sge/structure_cast.hpp>

sge::gui::widgets::graphics::graphics(
	widgets::parent_data const &_parent,
	widgets::parameters _params,
	const_image_ptr const _image)
: 
	base(
		_parent,
		_params
			.size_policy(
				sge::gui::size_policy(
					axis_policy::none,
					axis_policy::none)))
{
	buffer() = *_image;
}
