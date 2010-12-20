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


#include "../../image/view/make_impl.hpp"
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/export_symbol.hpp>

template
FCPPT_EXPORT_SYMBOL
sge::image2d::view::object const
sge::image::view::make<
	sge::image2d::view::object,
	sge::image2d::dim,
	sge::image2d::view::optional_pitch
>(
	image::raw_pointer,
	image2d::dim const &,
	image::color::format::type,
	image2d::view::optional_pitch const &
);

sge::image2d::view::object const
sge::image2d::view::make(
	image::raw_pointer const _data,
	image2d::dim const &_dim,
	image::color::format::type const _format,
	image2d::view::optional_pitch const &_pitch
)
{
	return
		sge::image::view::make<
			sge::image2d::view::object
		>(
			_data,
			_dim,
			_format,
			_pitch
		);
}
