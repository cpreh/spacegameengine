/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/viewport/manager.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manage_function.hpp>
#include <sge/viewport/resize_function.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/target_base_ptr.hpp>
#include <sge/window/instance.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <awl/window/event/resize.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>

class sge::viewport::manager::impl
{
	FCPPT_NONCOPYABLE(
		impl	
	);
public:
	explicit impl(
		sge::renderer::device &,
		viewport::resize_function const &
	);
	
	~impl();

	fcppt::signal::auto_connection
	manage_callback(
		viewport::manage_callback const &
	);
private:
	void
	on_resize(
		awl::window::event::resize const &
	);

	sge::renderer::target_base_ptr const target_;

	viewport::resize_function const resize_function_;

	fcppt::signal::scoped_connection const resize_connection_;

	typedef fcppt::signal::object<
		viewport::manage_function
	> manage_signal;

	manage_signal manage_signal_;
};

sge::viewport::manager::manager(
	renderer::device &_device,
	viewport::resize_function const &_resize_function
)
:
	impl_(
		fcppt::make_unique_ptr<
			impl
		>(
			std::tr1::ref(
				_device
			),
			_resize_function
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

sge::viewport::manager::impl::impl(
	sge::renderer::device &_device,
	viewport::resize_function const &_resize_function
)
:
	target_(
		_device.onscreen_target()
	),
	resize_function_(
		_resize_function
	),
	resize_connection_(
		_device.window()->awl_window_event_processor()->resize_callback(
			std::tr1::bind(
				&impl::on_resize,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	manage_signal_()
{
}

sge::viewport::manager::impl::~impl()
{
}

fcppt::signal::auto_connection
sge::viewport::manager::impl::manage_callback(
	viewport::manage_callback const &_callback
)
{
	return
		manage_signal_.connect(
			_callback
		);
}

void
sge::viewport::manager::impl::on_resize(
	awl::window::event::resize const &_resize
)
{
	if(
		resize_function_
	)
		target_->viewport(
			resize_function_(
				_resize
			)
		);

	manage_signal_();
}
