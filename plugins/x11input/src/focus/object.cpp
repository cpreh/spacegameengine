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


#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_event.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_event.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_event.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/x11input/device/parameters.hpp>
#include <sge/x11input/device/window_demuxer.hpp>
#include <sge/x11input/device/window_event.hpp>
#include <sge/x11input/focus/looked_up_string.hpp>
#include <sge/x11input/focus/lookup_string.hpp>
#include <sge/x11input/focus/object.hpp>
#include <sge/x11input/key/event_to_sge_code.hpp>
#include <sge/x11input/key/is_repeated.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <sge/x11input/xim/const_optional_method_ref.hpp>
#include <sge/x11input/xim/context.hpp>
#include <sge/x11input/xim/get_filter_events.hpp>
#include <sge/x11input/xim/method.hpp>
#include <awl/backends/x11/system/event/type.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <awl/backends/x11/window/event/scoped_mask.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::x11input::focus::object::object(
	fcppt::log::object &_log,
	awl::backends::x11::window::event::processor &_window_processor,
	sge::x11input::device::parameters const &_parameters,
	sge::x11input::xim::const_optional_method_ref const &_xim_method
)
:
	sge::input::focus::object(),
	sge::x11input::device::object(
		_parameters.id()
	),
	log_{
		_log
	},
	key_signal_(),
	key_repeat_signal_(),
	char_signal_(),
	in_signal_(),
	out_signal_(),
	window_(
		_parameters.window()
	),
	xim_context_{
		fcppt::optional::map(
			_xim_method,
			[
				&_parameters
			](
				fcppt::reference<
					sge::x11input::xim::method const
				> const _method
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::x11input::xim::context
					>(
						_method.get().get(),
						_parameters.window()
					);
			}
		)
	},
	scoped_event_mask_(
		fcppt::optional::map(
			xim_context_,
			[
				&_window_processor
			](
				xim_context_unique_ptr const &_context
			)
			{
				return
					fcppt::make_unique_ptr<
						awl::backends::x11::window::event::scoped_mask
					>(
						_window_processor,
						sge::x11input::xim::get_filter_events(
							*_context
						)
					);
			}
		)
	),
	connections_(
		fcppt::assign::make_container<
			fcppt::signal::auto_connection_container
		>(
			_parameters.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyPress
				),
				_parameters.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::focus::object::on_key_press,
						this,
						std::placeholders::_1
					)
				}
			),
			_parameters.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_KeyRelease
				),
				_parameters.id(),
				sge::x11input::device::window_demuxer::callback{
					std::bind(
						&sge::x11input::focus::object::on_key_release,
						this,
						std::placeholders::_1
					)
				}
			),
			_parameters.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_FocusIn
				),
				_parameters.id(),
				sge::x11input::device::window_demuxer::callback{
					[
						this
					](
						sge::x11input::device::window_event const &
					)
					{
						fcppt::optional::maybe_void(
							xim_context_,
							[](
								xim_context_unique_ptr const &_context
							)
							{
								::XSetICFocus(
									_context->get()
								);
							}
						);

						in_signal_(
							sge::input::focus::in_event{}
						);
					}
				}
			),
			_parameters.window_demuxer().register_callback(
				awl::backends::x11::system::event::type(
					XI_FocusOut
				),
				_parameters.id(),
				sge::x11input::device::window_demuxer::callback{
					[
						this
					](
						sge::x11input::device::window_event const &
					)
					{
						out_signal_(
							sge::input::focus::out_event{}
						);

						fcppt::optional::maybe_void(
							xim_context_,
							[](
								xim_context_unique_ptr const &_context
							)
							{
								::XUnsetICFocus(
									_context->get()
								);
							}
						);
					}
				}
			)
		)
	)
{
}

sge::x11input::focus::object::~object()
{
}

fcppt::signal::auto_connection
sge::x11input::focus::object::key_callback(
	sge::input::focus::key_callback const &_callback
)
{
	return
		key_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::key_repeat_callback(
	sge::input::focus::key_repeat_callback const &_callback
)
{
	return
		key_repeat_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::char_callback(
	sge::input::focus::char_callback const &_callback
)
{
	return
		char_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::in_callback(
	sge::input::focus::in_callback const &_callback
)
{
	return
		in_signal_.connect(
			_callback
		);
}

fcppt::signal::auto_connection
sge::x11input::focus::object::out_callback(
	sge::input::focus::out_callback const &_callback
)
{
	return
		out_signal_.connect(
			_callback
		);
}

void
sge::x11input::focus::object::on_key_press(
	sge::x11input::device::window_event const &_event
)
{
	sge::x11input::key::repeated const repeated{
		sge::x11input::key::is_repeated(
			_event.get()
		)
	};

	fcppt::optional::maybe(
		xim_context_,
		[
			this,
			repeated,
			&_event
		]{
			this->process_key_down(
				repeated,
				sge::x11input::key::event_to_sge_code(
					window_.display(),
					_event.get()
				)
			);
		},
		[
			this,
			repeated,
			&_event
		](
			xim_context_unique_ptr const &_context
		)
		{
			sge::x11input::focus::looked_up_string const lookup(
				sge::x11input::focus::lookup_string(
					log_,
					*_context,
					_event.get()
				)
			);

			this->process_key_down(
				repeated,
				lookup.key_code()
			);

			for(
				auto const &element
				:
				lookup.char_codes()
			)
				char_signal_(
					sge::input::focus::char_event(
						element
					)
				);
		}
	);
}

void
sge::x11input::focus::object::on_key_release(
	sge::x11input::device::window_event const &_event
)
{
	key_signal_(
		sge::input::focus::key_event(
			sge::input::focus::key{
				sge::x11input::key::event_to_sge_code(
					window_.display(),
					_event.get()
				)
			},
			sge::input::key::pressed{
				false
			}
		)
	);
}

void
sge::x11input::focus::object::process_key_down(
	sge::x11input::key::repeated const _repeated,
	sge::input::key::code const _key_code
)
{
	sge::input::focus::key const key(
		_key_code
	);

	if(
		_repeated.get()
	)
		key_repeat_signal_(
			sge::input::focus::key_repeat_event(
				key
			)
		);
	else
		key_signal_(
			sge::input::focus::key_event(
				key,
				sge::input::key::pressed{
					true
				}
			)
		);
}
