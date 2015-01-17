/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <sge/src/renderer/instantiate_float.hpp>
#include <sge/src/texture/logger.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/componentwise_equal.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/to_dim.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <limits>
#include <ostream>
#include <fcppt/config/external_end.hpp>


template<
	typename T
>
typename boost::enable_if<
	fcppt::type_traits::is_float_or_double<
		T
	>,
	fcppt::math::box::rect<
		T
	>
>::type const
sge::texture::area_texc(
	sge::texture::part const &_part,
	fcppt::math::vector::static_<
		T,
		2
	> const &_repeat
)
{
	typedef fcppt::math::vector::static_<
		T,
		2
	> vector_type;

	if(
		!fcppt::math::vector::componentwise_equal(
			_repeat,
			vector_type(
				1.f,
				1.f
			),
			std::numeric_limits<
				T
			>::epsilon()
		)
		&& !_part.repeatable()
	)
		FCPPT_LOG_WARNING(
			sge::texture::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("texture not repeatable but repetition is ")
				<< _repeat
				<< FCPPT_TEXT('!')
		);

	typedef fcppt::math::box::rect<
		T
	> ret_type;

	ret_type ret(
		sge::renderer::lock_rect_to_coords<
			T
		>(
			_part.area(),
			_part.texture().size()
		)
	);

	ret.size(
		fcppt::math::vector::to_dim(
			_repeat
			*
			ret.size()
		)
	);

	return
		ret;
}

#define SGE_TEXTURE_INSTANTIATE_AREA_TEXC(\
	ftype\
)\
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
boost::enable_if< \
	fcppt::type_traits::is_float_or_double< \
		ftype \
	>, \
	fcppt::math::box::rect<\
		ftype\
	> \
>::type const \
sge::texture::area_texc<\
	ftype\
>( \
	sge::texture::part const &,\
	fcppt::math::vector::static_<\
		ftype,\
		2\
	> const &\
)

SGE_RENDERER_INSTANTIATE_FLOAT(
	SGE_TEXTURE_INSTANTIATE_AREA_TEXC
)
