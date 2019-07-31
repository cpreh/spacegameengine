//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/get_extensions.hpp>
#include <sge/opengl/glx/system.hpp>
#include <sge/opengl/glx/visual/create.hpp>
#include <sge/opengl/glx/visual/get_srgb_flag.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/alternative.hpp>
#include <fcppt/optional/from_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::system::system(
	fcppt::log::object &_log,
	awl::backends::x11::system::object &_awl_system
)
:
	sge::opengl::backend::system(),
	log_{
		_log
	},
	awl_system_(
		_awl_system
	),
	get_proc_address_(
		fcppt::optional::alternative(
			fcppt::optional::from_pointer(
				::glXGetProcAddress
			),
			fcppt::const_(
				fcppt::optional::from_pointer(
					::glXGetProcAddressARB
				)
			)
		)
	),
	extensions_(
		sge::opengl::glx::get_extensions(
			_awl_system.display()
		)
	),
	srgb_flag_(
		sge::opengl::glx::visual::get_srgb_flag(
			extensions_
		)
	)
{
}

sge::opengl::glx::system::~system()
{
}

awl::visual::object_unique_ptr
sge::opengl::glx::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		sge::opengl::glx::visual::create(
			srgb_flag_,
			awl_system_,
			_pixel_format
		);
}

sge::opengl::backend::context_unique_ptr
sge::opengl::glx::system::create_context(
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr<
				sge::opengl::glx::context
			>(
				log_,
				fcppt::cast::dynamic_exn<
					awl::backends::x11::window::base &
				>(
					_window.awl_object()
				),
				get_proc_address_
			)
		);
}
