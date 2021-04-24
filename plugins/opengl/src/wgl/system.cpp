//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/get_config.hpp>
#include <sge/opengl/wgl/system.hpp>
#include <sge/opengl/windows/visual/create.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::opengl::wgl::system::system(
	awl::system::object &_awl_system
)
:
	sge::opengl::backend::system(),
	config_(
		sge::opengl::wgl::get_config(
			_awl_system
		)
	)
{
}

sge::opengl::wgl::system::~system()
= default;

awl::visual::object_unique_ptr
sge::opengl::wgl::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::windows::visual::create(
			config_.visual_config(),
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::wgl::system::create_context(
	sge::window::object_ref const _window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr<
				sge::opengl::wgl::context
			>(
				fcppt::optional::to_exception(
					fcppt::cast::dynamic<
						awl::backends::windows::window::object
					>(
						_window.get().awl_object()
					),
					[]{
						return
							sge::renderer::exception{
								FCPPT_TEXT("Window passed to opengl::wgl::system is not a Windows window.")
							};
					}
				).get()
			)
		);
}


