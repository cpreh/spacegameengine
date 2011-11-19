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


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/src/renderer/instantiate_float.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Ret
>
typename boost::enable_if<
	boost::is_floating_point<
		Ret
	>,
	typename fcppt::math::box::rect<
		Ret
	>::type const
>::type
sge::renderer::lock_rect_to_coords(
	renderer::lock_rect const &_rect,
	renderer::dim2 const &_dim
)
{
	typedef typename fcppt::math::box::rect<
		Ret
	>::type ret_type;

	ret_type const srect(
		fcppt::math::box::structure_cast<
			ret_type
		>(
			_rect
		)
	);

	typedef typename fcppt::math::dim::static_<
		Ret,
		2
	>::type sdim_type;

	sdim_type const sdim(
		fcppt::math::dim::structure_cast<
			sdim_type
		>(
			_dim
		)
	);

	return
		ret_type(
			typename ret_type::vector(
				srect.left() / sdim.w(),
				srect.top() / sdim.h()
			),
			srect.size() / sdim
		);
}

#define SGE_RENDERER_INSTANTIATE_LOCK_RECT_TO_COORDS(\
	floattype\
) \
template \
FCPPT_EXPORT_SYMBOL \
boost::enable_if< \
	boost::is_floating_point< \
		floattype \
	>, \
	fcppt::math::box::rect< \
		floattype \
	>::type const \
>::type \
sge::renderer::lock_rect_to_coords<\
	floattype \
>(\
	renderer::lock_rect const &, \
	renderer::dim2 const &\
)

SGE_RENDERER_INSTANTIATE_FLOAT(
	SGE_RENDERER_INSTANTIATE_LOCK_RECT_TO_COORDS
)
