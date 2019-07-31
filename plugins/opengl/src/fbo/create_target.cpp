//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/fbo/create_target.hpp>
#include <sge/opengl/fbo/target.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::target::offscreen_unique_ptr
sge::opengl::fbo::create_target(
	sge::opengl::context::object &_context
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::target::offscreen
		>(
			fcppt::make_unique_ptr<
				sge::opengl::fbo::target
			>(
				_context
			)
		);
}
