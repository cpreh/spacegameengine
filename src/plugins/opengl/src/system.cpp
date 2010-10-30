/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../system.hpp"
#include "../device.hpp"
#include <sge/window/instance.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <awl/window/create_system.hpp>
#include <awl/window/parameters.hpp>
#include <awl/window/system.hpp>

sge::opengl::system::system()
:
	weak_ref_()
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device_ptr const
sge::opengl::system::create_renderer(
	renderer::parameters const &_param,
	renderer::adapter_type const _adapter,
	window::instance_ptr const _wnd
)
{
	if(
		weak_ref_.lock()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("The opengl plugin may only have one renderer!")
		);

	renderer::device_ptr const ret(
		fcppt::make_shared_ptr<
			device
		>(
			_param,
			_adapter,
			_wnd
		)
	);

	weak_ref_ = ret;

	return ret;
}

sge::window::instance_ptr const
sge::opengl::system::create_window(
	window::parameters const &_param,
	renderer::parameters const &_rparam
)
{
	return
		fcppt::make_shared_ptr<
			sge::window::instance
		>(
			awl::window::create_system()->create(
				awl::window::parameters(
				)
			)
		);
}
