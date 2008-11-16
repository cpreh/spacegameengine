/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/subimage_view.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

namespace
{

template<
	typename View
>
View const
subimage_view_impl(
	View const &,
	sge::renderer::lock_rect const &);

}

sge::renderer::image_view const
sge::renderer::subimage_view(
	image_view const &src,
	lock_rect const &lr)
{
	return subimage_view_impl(
		src,
		lr);
}

sge::renderer::const_image_view const
sge::renderer::subimage_view(
	const_image_view const &src,
	lock_rect const &lr)
{
	return subimage_view_impl(
		src,
		lr);
}

namespace
{

template<
	typename View
>
View const
subimage_view_impl(
	View const &v,
	sge::renderer::lock_rect const &r)
{
	return boost::gil::subimage_view(
		v,
		static_cast<int>(r.left()),
		static_cast<int>(r.top()),
		static_cast<int>(r.w()),
		static_cast<int>(r.h()));
}

}
