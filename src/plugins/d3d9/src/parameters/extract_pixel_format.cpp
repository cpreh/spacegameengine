/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/visual.hpp>
#include <sge/d3d9/parameters/extract_pixel_format.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/visual/object.hpp>


sge::renderer::pixel_format::object
sge::d3d9::parameters::extract_pixel_format(
	awl::visual::object const &_visual
)
{
	// TODO: Is there a sane default if this fails?
	return
		dynamic_cast<
			sge::d3d9::visual const &
		>(
			_visual
		).pixel_format();
}
