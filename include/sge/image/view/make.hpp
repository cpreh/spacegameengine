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


#ifndef SGE_IMAGE_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MAKE_HPP_INCLUDED

#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/detail/instantiate_symbol.hpp>
#include <sge/image/traits/dim.hpp>
#include <sge/image/traits/optional_pitch.hpp>
#include <sge/image/traits/view.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename Tag
>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
typename image::traits::view<
	Tag
>::type const
make(
	image::raw_pointer const, // this const is here because VC++ screws the type of the function up!
	typename image::traits::dim<
		Tag
	>::type const &,
	image::color::format::type,
	typename image::traits::optional_pitch<
		Tag
	>::type const &
);

}
}
}

#endif
