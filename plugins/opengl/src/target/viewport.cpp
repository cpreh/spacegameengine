//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/target/set_flipped_area.hpp>
#include <sge/opengl/target/viewport.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::target::viewport(
	sge::renderer::target::viewport const &_viewport,
	sge::renderer::screen_unit const _height
)
{
	sge::opengl::target::set_flipped_area(
		::glViewport,
		_viewport.get(),
		_height
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glViewport failed"),
		sge::renderer::exception
	)
}
