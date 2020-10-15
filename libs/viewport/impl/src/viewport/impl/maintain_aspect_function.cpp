//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <sge/viewport/impl/center.hpp>
#include <sge/viewport/impl/maintain_aspect_function.hpp>
#include <sge/window/dim.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/rational.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

using
rational
=
boost::rational<
	sge::viewport::fractional_aspect::value_type
>;

rational::int_type
truncate_rational(
	rational const &_rational
)
{
	return
		_rational.numerator()
		/
		_rational.denominator();
}

}

sge::renderer::target::viewport
sge::viewport::impl::maintain_aspect_function(
	awl::window::event::resize const &_event,
	sge::viewport::fractional_aspect const _aspect
)
{
	rational const desired(
		_aspect.num(),
		_aspect.denom()
	);

	rational::int_type const width(
		_event.dim().w()
	);

	rational::int_type const height(
		_event.dim().h()
	);

	rational const actual(
		width,
		height
	);

	if(
		actual == desired
	)
	{
		return
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					fcppt::math::vector::null<
						sge::renderer::pixel_rect::vector
					>(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim,
						fcppt::cast::to_signed_fun
					>(
						fcppt::math::dim::structure_cast<
							sge::renderer::screen_size,
							fcppt::cast::size_fun
						>(
							_event.dim()
						)
					)
				)
			);
	}

	bool const horizontal(
		actual > desired
	);

	rational const difference(
		horizontal
		?
			desired / actual
		:
			actual / desired
	);

	return
		sge::viewport::impl::center(
			horizontal
			?
				sge::window::dim(
					truncate_rational(
						rational(
							width
						)
						* difference
					),
					height
				)
			:
				sge::window::dim(
					width,
					truncate_rational(
						rational(
							height
						)
						* difference
					)
				)
			,
			fcppt::math::dim::structure_cast<
				sge::window::dim,
				fcppt::cast::size_fun
			>(
				_event.dim()
			)
		);
}
