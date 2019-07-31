//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/target/read_pixels.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/screen_size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_void_ptr.hpp>


void
sge::opengl::target::read_pixels(
	sge::renderer::pixel_pos const _pos,
	sge::renderer::screen_size const _size,
	sge::opengl::color_order const _format,
	sge::opengl::color_base_type const _format_type,
	sge::renderer::raw_pointer const _dest
)
{
	sge::opengl::call(
		::glReadPixels,
		fcppt::cast::size<
			GLint
		>(
			_pos.x()
		),
		fcppt::cast::size<
			GLint
		>(
			_pos.y()
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_size.w()
			)
		),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				_size.h()
			)
		),
		_format.get(),
		_format_type.get(),
		fcppt::cast::to_void_ptr(
			_dest
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glReadPixels failed"),
		sge::renderer::exception
	)
}
