//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename Ret
>
std::enable_if_t<
	sge::renderer::is_valid_float_type<
		Ret
	>::value,
	fcppt::math::box::rect<
		Ret
	>
>
sge::renderer::lock_rect_to_coords(
	sge::renderer::lock_rect const &_rect,
	sge::renderer::dim2 const &_dim
)
{
	using
	ret_type
	=
	fcppt::math::box::rect<
		Ret
	>;

	auto const srect(
		fcppt::math::box::structure_cast<
			ret_type,
			fcppt::cast::int_to_float_fun
		>(
			_rect
		)
	);

	using
	sdim_type
	=
	fcppt::math::dim::static_<
		Ret,
		2
	>;

	auto const sdim(
		fcppt::math::dim::structure_cast<
			sdim_type,
			fcppt::cast::int_to_float_fun
		>(
			_dim
		)
	);

	return
		// TODO(philipp): Make a function in fcppt::math::box for this
		ret_type(
			typename
			ret_type::vector{
				srect.left()
				/
				sdim.w(),
				srect.top()
				/
				sdim.h()
			},
			(
				srect.size()
				/
				sdim
			).get_unsafe()
		);
}

#define SGE_RENDERER_INSTANTIATE_LOCK_RECT_TO_COORDS(\
	floattype\
) \
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
std::enable_if_t< \
	sge::renderer::is_valid_float_type< \
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

SGE_RENDERER_INSTANTIATE_LOCK_RECT_TO_COORDS(
	float
);

SGE_RENDERER_INSTANTIATE_LOCK_RECT_TO_COORDS(
	double
);
