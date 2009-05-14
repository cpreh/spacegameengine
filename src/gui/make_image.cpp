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


#include <sge/gui/make_image.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/dim.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/renderer/image_view.hpp>
#include <sge/image/object.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/variant/object_impl.hpp>

sge::gui::image_ptr const sge::gui::make_image(
	sge::image::object_ptr _image)
{
	sge::gui::image_ptr i(
		new gui::image(
			math::dim::structure_cast<dim>(
				_image->dim()
			)
		)
	);

	renderer::copy_and_convert_pixels(
		_image->view(),
		renderer::image_view(
			i->view()));
	
	return i;
}
