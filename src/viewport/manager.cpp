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


#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/src/viewport/detail/manager_impl.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/optional_resize_callback_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/signal/auto_connection.hpp>


sge::viewport::manager::manager(
	sge::renderer::device::core &_device,
	sge::window::object &_window,
	sge::viewport::optional_resize_callback const &_resize_callback
)
:
	impl_(
		fcppt::make_unique_ptr_fcppt<
			sge::viewport::detail::manager_impl
		>(
			_device,
			_window,
			_resize_callback
		)
	)
{
}

sge::viewport::manager::~manager()
{
}

fcppt::signal::auto_connection
sge::viewport::manager::manage_callback(
	sge::viewport::manage_callback const &_callback
)
{
	return
		impl_->manage_callback(
			_callback
		);
}

void
sge::viewport::manager::resize_callback(
	sge::viewport::optional_resize_callback const &_resize_callback
)
{
	impl_->resize_callback(
		_resize_callback
	);
}

sge::renderer::target::viewport const
sge::viewport::manager::viewport() const
{
	return
		impl_->viewport();
}
