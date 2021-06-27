//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/renderer/is_valid_float_type.hpp>
#include <sge/renderer/lock_rect_to_coords.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/texture/area_texc.hpp>
#include <sge/texture/exception.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/componentwise_equal.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/to_dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <ostream>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename T
>
std::enable_if_t<
	sge::renderer::is_valid_float_type<
		T
	>::value,
	fcppt::math::box::rect<
		T
	>
>
sge::texture::area_texc(
	sge::texture::part const &_part,
	fcppt::math::vector::static_<
		T,
		2
	> const &_repeat
)
{
	using
	vector_type
	=
	fcppt::math::vector::static_<
		T,
		2
	>;

	// FIXME: Use optionals for repetition
	if(
		!fcppt::math::vector::componentwise_equal(
			_repeat,
			vector_type(
				fcppt::literal<
					T
				>(
					1
				),
				fcppt::literal<
					T
				>(
					1
				)
			),
			std::numeric_limits<
				T
			>::epsilon()
		)
		&& !_part.repeatable()
	)
	{
		throw
			sge::texture::exception{
				FCPPT_TEXT("texture not repeatable but repetition is ")
				+
				fcppt::output_to_fcppt_string(
					_repeat
				)
				+
				FCPPT_TEXT('!')
			};
	}

	using
	ret_type
	=
	fcppt::math::box::rect<
		T
	>;

	ret_type const coords(
		sge::renderer::lock_rect_to_coords<
			T
		>(
			_part.area(),
			_part.texture().size()
		)
	);

	return
		ret_type(
			coords.pos(),
			fcppt::math::vector::to_dim(
				_repeat
				*
				coords.size()
			)
		);
}

#define SGE_TEXTURE_INSTANTIATE_AREA_TEXC(\
	floattype\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
std::enable_if_t< \
	sge::renderer::is_valid_float_type< \
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

SGE_TEXTURE_INSTANTIATE_AREA_TEXC(
	float
);

SGE_TEXTURE_INSTANTIATE_AREA_TEXC(
	double
);
