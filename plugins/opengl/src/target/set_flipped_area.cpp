//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/target/area_function.hpp>
#include <sge/opengl/target/set_flipped_area.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


void
sge::opengl::target::set_flipped_area(
	sge::opengl::target::area_function _function,
	sge::renderer::pixel_rect const &_area,
	sge::renderer::screen_unit const _height
)
{
	_function(
		fcppt::cast::size<
			GLint
		>(
			_area.pos().x()
		),
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_height
			)
			-
			_area.size().h()
			-
			_area.pos().y()
		),
		fcppt::cast::size<
			GLsizei
		>(
			_area.size().w()
		),
		fcppt::cast::size<
			GLsizei
		>(
			_area.size().h()
		)
	);

	// checking is done in the calling function
}
