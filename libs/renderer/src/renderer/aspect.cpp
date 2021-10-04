//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/aspect.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/screen_size.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/div.hpp>
#include <fcppt/optional/object_impl.hpp>


fcppt::optional::object<
	sge::renderer::scalar
>
sge::renderer::aspect(
	sge::renderer::screen_size const &_size
)
{
	auto const width(
		fcppt::cast::int_to_float<
			sge::renderer::scalar
		>(
			_size.w()
		)
	);

	auto const height(
		fcppt::cast::int_to_float<
			sge::renderer::scalar
		>(
			_size.h()
		)
	);

	return
		width > height
		?
			fcppt::math::div(
				width,
				height
			)
		:
			fcppt::math::div(
				height,
				width
			)
		;
}
