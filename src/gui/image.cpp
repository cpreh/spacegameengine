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
#include <sge/gui/image_view.hpp>
#include <boost/gil/image.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/gui/unit.hpp>

sge::gui::image::image()
: 
	impl_()
{
}

sge::gui::image::image(
	dim const &d)
: 
	impl_(
		static_cast<impl_type::coord_t>(d.w()),
		static_cast<impl_type::coord_t>(d.h()))
{
}

sge::gui::dim const sge::gui::image::size() const
{
	return 
		dim(
			static_cast<unit>(
				impl_.width()),
			static_cast<unit>(
				impl_.height()));
}

sge::gui::image_view const sge::gui::image::view()
{
	return 
		image_view(
			boost::gil::view(
				impl_));
}

sge::gui::const_image_view const sge::gui::image::const_view() const
{
	return 
		const_image_view(
			boost::gil::const_view(
				impl_));
}

void sge::gui::image::resize(
	dim const &d)
{
	impl_.recreate(
		static_cast<impl_type::coord_t>(
			d.w()),
		static_cast<impl_type::coord_t>(
			d.h()));
}
