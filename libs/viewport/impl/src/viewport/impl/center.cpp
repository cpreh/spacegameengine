//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/impl/center.hpp>
#include <sge/window/dim.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


namespace
{

sge::renderer::pixel_unit
center_position(
	sge::window::dim::value_type const _target_size,
	sge::window::dim::value_type const _window_size
)
{
	FCPPT_ASSERT_PRE(
		_window_size >= _target_size
	);

	return
		fcppt::cast::size<
			sge::renderer::pixel_unit
		>(
			fcppt::cast::to_signed(
			(
				_window_size
				-
				_target_size
				)
				/ 2U
			)
		);
}

}

sge::renderer::target::viewport
sge::viewport::impl::center(
	sge::window::dim const &_ref_dim,
	sge::window::dim const &_window_dim
)
{
	return
		_ref_dim.w()
		> _window_dim.w()
		||
		_ref_dim.h()
		> _window_dim.h()
		?
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					fcppt::math::vector::null<
						sge::renderer::pixel_rect::vector
					>(),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim,
						fcppt::cast::to_signed_fun
					>(
						_window_dim
					)
				)
			)
		:
			sge::renderer::target::viewport(
				sge::renderer::pixel_rect(
					sge::renderer::pixel_rect::vector(
						center_position(
							_ref_dim.w(),
							_window_dim.w()
						),
						center_position(
							_ref_dim.h(),
							_window_dim.h()
						)
					),
					fcppt::math::dim::structure_cast<
						sge::renderer::pixel_rect::dim,
						fcppt::cast::to_signed_fun
					>(
						_ref_dim
					)
				)
			);
}
