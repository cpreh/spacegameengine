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


#include "../../image/view/make_const_impl.hpp"
#include <sge/image3d/view/make_const.hpp>
#include <sge/image3d/view/make.hpp>
#include <sge/image3d/view/to_const.hpp>
#include <sge/image/raw_pointer.hpp>

sge::image3d::view::const_object const
sge::image3d::view::make_const(
	image::const_raw_pointer const _data,
	image3d::dim const &_dim,
	image::color::format::type const _format,
	image3d::view::optional_pitch const &_pitch
)
{
	return
		sge::image::view::make_const<
			sge::image3d::view::const_object
		>(
			const_cast<
				image::raw_pointer
			>(
				_data
			),
			_dim,
			_format,
			_pitch,
			&view::make,
			&view::to_const
		);
}
