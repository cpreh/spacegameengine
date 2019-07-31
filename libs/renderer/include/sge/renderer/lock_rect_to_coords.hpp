//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED

#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Transforms a lock rect into texture coordinates

\ingroup sge_renderer

Calculates the texture coordinates for \a area using the texture size \a size.

\param area The portion of the texture to calculate the coordinates for

\param size The size of the texture

\return The texture coordinates in [(0,0),(1,1)]

\warning The behaviour is undefined if \a area lies outside of \a size
*/
template<
	typename Ret
>
SGE_RENDERER_DETAIL_SYMBOL
std::enable_if_t<
	fcppt::type_traits::is_float_or_double<
		Ret
	>::value,
	fcppt::math::box::rect<
		Ret
	>
>
lock_rect_to_coords(
	sge::renderer::lock_rect const &area,
	sge::renderer::dim2 const &size
);

}
}

#define SGE_RENDERER_DETAIL_DECLARE_LOCK_RECT_TO_COORDS(\
	floattype\
)\
extern \
template \
SGE_RENDERER_DETAIL_SYMBOL \
std::enable_if_t< \
	fcppt::type_traits::is_float_or_double< \
		floattype \
	>::value, \
	fcppt::math::box::rect< \
		floattype \
	> \
> \
sge::renderer::lock_rect_to_coords<\
	floattype \
>(\
	sge::renderer::lock_rect const &, \
	sge::renderer::dim2 const &\
)

SGE_RENDERER_DETAIL_DECLARE_LOCK_RECT_TO_COORDS(
	float
);

SGE_RENDERER_DETAIL_DECLARE_LOCK_RECT_TO_COORDS(
	double
);

#endif
