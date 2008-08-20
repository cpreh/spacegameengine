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


#include <sge/renderer/image_view_factory.hpp>
#include <sge/math/rect_impl.hpp>
#include <boost/gil/extension/dynamic_image/image_view_factory.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

// FIXME: unify these
sge::renderer::image_view const sge::renderer::subimage_view(
	image_view const &src,
	lock_rect const &lr)
{
	return boost::gil::subimage_view(
		src,
		static_cast<int>(lr.left()),
		static_cast<int>(lr.top()),
		static_cast<int>(lr.w()),
		static_cast<int>(lr.h()));
}

sge::renderer::const_image_view const sge::renderer::subimage_view(
	const_image_view const &src,
	lock_rect const &lr)
{
	return boost::gil::subimage_view(
		src,
		static_cast<int>(lr.left()),
		static_cast<int>(lr.top()),
		static_cast<int>(lr.w()),
		static_cast<int>(lr.h()));
}
