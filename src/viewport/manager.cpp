/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/device_fwd.hpp>
#include <sge/src/viewport/detail/manager_impl.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/resize_function.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/signal/auto_connection.hpp>


sge::viewport::manager::manager(
	renderer::device &_device,
	sge::window::object &_window,
	viewport::resize_function const &_resize_function
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::viewport::detail::manager_impl
		>(
			fcppt::ref(
				_device
			),
			fcppt::ref(
				_window
			),
			fcppt::cref(
				_resize_function
			)
		)
	)
{
}

sge::viewport::manager::~manager()
{
}

fcppt::signal::auto_connection
sge::viewport::manager::manage_callback(
	viewport::manage_callback const &_callback
)
{
	return
		impl_->manage_callback(
			_callback
		);
}
