/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/logger.hpp>
#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current_fwd.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/glx/context.hpp>
#include <sge/opengl/glx/get_extensions.hpp>
#include <sge/opengl/glx/system.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/opengl/glx/visual/create.hpp>
#include <sge/opengl/glx/visual/get_srgb_flag.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_alternative.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/optional_from_pointer.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::system::system(
	awl::backends::x11::system::object &_awl_system
)
:
	awl_system_(
		_awl_system
	),
	get_proc_address_(
		fcppt::optional_alternative(
			fcppt::optional_from_pointer(
				::glXGetProcAddress
			),
			fcppt::optional_from_pointer(
				::glXGetProcAddressARB
			)
		)
	),
	swap_functions_(
		fcppt::optional_bind_construct(
			get_proc_address_,
			[](
				sge::opengl::glx::proc_address_function _proc_address
			)
			{
				return
					sge::opengl::glx::swap_functions(
						_proc_address
					);
			}
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
	awl::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::context
		>(
			fcppt::make_unique_ptr<
				sge::opengl::glx::context
			>(
				fcppt::cast::static_downcast<
					awl::backends::x11::window::object &
				>(
					_window
				)
			)
		);
}

void
sge::opengl::glx::system::vsync(
	sge::opengl::backend::scoped_current const &,
	awl::window::object &_awl_window,
	sge::renderer::display_mode::vsync const _vsync
)
{
	if(
		_vsync
		==
		sge::renderer::display_mode::vsync::on
	)
		fcppt::maybe(
			swap_functions_,
			[]{
				FCPPT_LOG_ERROR(
					sge::opengl::logger(),
					fcppt::log::_
						<<
						FCPPT_TEXT("GLX extensions not available.")
						FCPPT_TEXT(" Setting vsync is not supported.")

				);
			},
			[
				&_awl_window
			](
				sge::opengl::glx::swap_functions const &_swap_functions
			)
			{
				sge::opengl::glx::vsync(
					_swap_functions,
					fcppt::cast::static_downcast<
						awl::backends::x11::window::object &
					>(
						_awl_window
					).display()
				);
			}
		);
}
