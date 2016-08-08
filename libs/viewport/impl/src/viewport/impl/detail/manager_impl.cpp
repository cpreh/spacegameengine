/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/device/core.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/impl/detail/manager_impl.hpp>
#include <sge/window/object.hpp>
#include <awl/window/event/processor.hpp>
#include <awl/window/event/resize_callback.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::viewport::detail::manager_impl::manager_impl(
	sge::renderer::device::core &_device,
	sge::window::object &_window,
	sge::viewport::optional_resize_callback const &_resize_callback
)
:
	target_(
		_device.onscreen_target()
	),
	resize_callback_(
		_resize_callback
	),
	resize_connection_(
		_window.awl_window_event_processor().resize_callback(
			awl::window::event::resize_callback{
				std::bind(
					&sge::viewport::detail::manager_impl::on_resize,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	manage_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::viewport::detail::manager_impl::~manager_impl()
{
}

fcppt::signal::auto_connection
sge::viewport::detail::manager_impl::manage_callback(
	sge::viewport::manage_callback const &_callback
)
{
	return
		manage_signal_.connect(
			_callback
		);
}

void
sge::viewport::detail::manager_impl::resize_callback(
	sge::viewport::optional_resize_callback const &_resize_callback
)
{
	resize_callback_ =
		_resize_callback;
}

sge::renderer::target::viewport
sge::viewport::detail::manager_impl::viewport() const
{
	return
		target_.viewport();
}

void
sge::viewport::detail::manager_impl::on_resize(
	awl::window::event::resize const &_resize
)
{
	fcppt::optional::maybe_void(
		resize_callback_,
		[
			&_resize,
			this
		](
			sge::viewport::resize_callback const &_callback
		)
		{
			target_.viewport(
				_callback(
					_resize
				)
			);
		}
	);

	manage_signal_(
		this->viewport()
	);
}
