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


#include <sge/gui/image.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::gui::image::image()
:
	impl_()
{}

sge::gui::image::image(
	dim const &dim_
)
:
	impl_(
		sge::math::dim::structure_cast<
			sge::image::dim_type
		>(
			dim_
		)
	)
{}

sge::gui::dim const
sge::gui::image::size() const
{
	return sge::math::dim::structure_cast<
		sge::gui::dim
	>(
		impl_.dim()
	);
}

sge::gui::image_view const
sge::gui::image::view()
{
	return impl_.view();
}

sge::gui::const_image_view const
sge::gui::image::const_view() const
{
	return impl_.view();
}

void
sge::gui::image::resize(
	dim const &ndim
)
{
	impl_ =
		impl_type(
			sge::math::dim::structure_cast<
				impl_type::dim_type
			>(
				ndim
			)
		);
}
