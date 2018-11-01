/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED
#define SGE_TEXTURE_AREA_TEXC_HPP_INCLUDED

#include <sge/texture/part_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/vector/static_fwd.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace texture
{

template<
	typename T
>
SGE_TEXTURE_DETAIL_SYMBOL
std::enable_if_t<
	fcppt::type_traits::is_float_or_double<
		T
	>::value,
	fcppt::math::box::rect<
		T
	>
>
area_texc(
	sge::texture::part const &,
	fcppt::math::vector::static_<
		T,
		2
	> const &repeat
);

}
}

#define SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(\
	floattype\
)\
extern \
template \
SGE_TEXTURE_DETAIL_SYMBOL \
std::enable_if_t< \
	fcppt::type_traits::is_float_or_double< \
		floattype \
	>::value, \
	fcppt::math::box::rect<\
		floattype\
	> \
> \
sge::texture::area_texc<\
	floattype\
>( \
	sge::texture::part const &,\
	fcppt::math::vector::static_<\
		floattype,\
		2\
	> const &\
)

SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(
	float
);

SGE_TEXTURE_DETAIL_DECLARE_AREA_TEXC(
	double
);

#endif
