/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image2d/file.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::gui::image_ptr const
sge::gui::make_image(
	sge::image2d::file_ptr _image
)
{
	sge::gui::image_ptr i(
		fcppt::make_shared_ptr<
			gui::image
		>(
			fcppt::math::dim::structure_cast<dim>(
				_image->dim()
			)
		)
	);

	sge::image2d::algorithm::copy_and_convert(
		_image->view(),
		i->view()
	);

	return i;
}
