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


#include <sge/log/global.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


template<
	typename T
>
typename boost::enable_if<
	boost::is_floating_point<
		T
	>,
	typename fcppt::math::box::rect<
		T
	>::type
>::type const
sge::texture::area_texc(
	texture::part const &_part,
	typename fcppt::math::vector::static_<
		T,
		2
	>::type const &_repeat
)
{
	typedef typename fcppt::math::vector::static_<
		T,
		2
	>::type vector_type;

	if(
		_repeat
		!=
		vector_type(
			1.f,
			1.f
		)
		&& !_part.repeatable()
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("texture not repeatable but repetition is ")
				<< _repeat
				<< FCPPT_TEXT('!')
		);

	typedef typename fcppt::math::box::rect<
		T
	>::type ret_type;

	ret_type ret(
		renderer::lock_rect_to_coords<
			T
		>(
			_part.area(),
			_part.texture()->size()
		)
	);

	ret.size(
		fcppt::math::vector::structure_cast<
			typename ret_type::dim
		>(
			_repeat * ret.size()
		)
	);

	return ret;
}

#define SGE_TEXTURE_INSTANTIATE_AREA_TEXC(\
	ftype\
)\
template \
FCPPT_EXPORT_SYMBOL \
boost::enable_if< \
	boost::is_floating_point< \
		ftype \
	>, \
	fcppt::math::box::rect<\
		ftype\
	>::type \
>::type const \
sge::texture::area_texc<\
	ftype\
>( \
	sge::texture::part const &,\
	fcppt::math::vector::static_<\
		ftype,\
		2\
	>::type const &\
)

SGE_TEXTURE_INSTANTIATE_AREA_TEXC(
	float
);

SGE_TEXTURE_INSTANTIATE_AREA_TEXC(
	double
);
