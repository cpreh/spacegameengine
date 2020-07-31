//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/focus/key.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/string.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/device_function.hpp>
#include <sge/x11input/event/select.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/event/window_demuxer.hpp>
#include <sge/x11input/event/window_demuxer_ref.hpp>
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
#include <awl/backends/x11/Xlib.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/object_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/connection.hpp>
#include <awl/event/container.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/identity.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/reference_to_const.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::x11input::focus::object::object(
	sge::window::object_ref const _sge_window,
	fcppt::log::object_reference const _log,
	awl::backends::x11::window::object_ref const _window,
	sge::x11input::device::id const _id,
	sge::x11input::event::window_demuxer_ref const _window_demuxer,
	sge::x11input::xim::const_optional_method_ref const &_xim_method
)
:
	sge::input::focus::object{},
	fcppt::enable_shared_from_this<
		sge::x11input::focus::object
	>{},
	sge_window_{
		_sge_window
	},
	log_{
		_log
	},
	window_{
		fcppt::reference_to_const(
			fcppt::reference_to_base<
				awl::backends::x11::window::base
			>(
				_window
			)
		)
	},
	xim_context_{
		fcppt::optional::map(
			_xim_method,
			[
				&_window
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
						_window
					);
			}
		)
	},
	mask_connection_{
		fcppt::optional::map(
			xim_context_,
			[
				&_window
			](
				xim_context_unique_ptr const &_context
			)
			{
				return
					_window.get().add_event_mask(
						sge::x11input::xim::get_filter_events(
							*_context
						)
					);
			}
		)
	},
	event_connection_{
		_window_demuxer.get().on_event(
			_id,
			sge::x11input::event::device_function{
				[
					this
				](
					XIDeviceEvent const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
	sge::x11input::event::select<
		metal::list<
			sge::x11input::event::type_c<
				XI_KeyPress
			>,
			sge::x11input::event::type_c<
				XI_KeyRelease
			>,
			sge::x11input::event::type_c<
				XI_FocusIn
			>,
			sge::x11input::event::type_c<
				XI_FocusOut
			>
		>
	>(
		_window_demuxer.get(),
		_id
	);
}

sge::x11input::focus::object::~object()
= default;

sge::window::object &
sge::x11input::focus::object::window() const
{
	return
		sge_window_.get();
}

awl::event::container
sge::x11input::focus::object::on_event(
	XIDeviceEvent const &_event
)
{
	switch(
		_event.evtype
	)
	{
	case XI_KeyPress:
		return
			this->on_key_press(
				_event
			);
	case XI_KeyRelease:
		return
			fcppt::container::make<
				awl::event::container
			>(
				this->on_key_release(
					_event
				)
			);
	case XI_FocusIn:
		return
			fcppt::container::make<
				awl::event::container
			>(
				this->on_focus_in()
			);
	case XI_FocusOut:
		return
			fcppt::container::make<
				awl::event::container
			>(
				this->on_focus_out()
			);
	}

	return
		awl::event::container{};
}

awl::event::container
sge::x11input::focus::object::on_key_press(
	XIDeviceEvent const &_event
)
{
	sge::x11input::key::repeated const repeated{
		sge::x11input::key::is_repeated(
			_event
		)
	};

	return
		fcppt::optional::maybe(
			xim_context_,
			[
				this,
				repeated,
				&_event
			]{
				return
					fcppt::container::make<
						awl::event::container
					>(
						this->process_key_down(
							repeated,
							sge::x11input::key::event_to_sge_code(
								window_.get().display().get(),
								_event
							)
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
						log_.get(),
						*_context,
						_event
					)
				);

				return
					fcppt::container::make<
						awl::event::container
					>(
						this->process_key_down(
							repeated,
							lookup.key_code()
						),
						fcppt::unique_ptr_to_base<
							awl::event::base
						>(
							fcppt::make_unique_ptr<
								sge::input::focus::event::text
							>(
								sge::input::focus::shared_ptr{
									this->fcppt_shared_from_this()
								},
								fcppt::algorithm::map<
									sge::input::focus::string
								>(
									lookup.char_codes(),
									fcppt::identity{}
								)
							)
						)
					);
			}
		);
}

awl::event::base_unique_ptr
sge::x11input::focus::object::on_key_release(
	XIDeviceEvent const &_event
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::focus::event::key
			>(
				sge::input::focus::shared_ptr{
					this->fcppt_shared_from_this()
				},
				sge::input::focus::key{
					sge::x11input::key::event_to_sge_code(
						window_.get().display().get(),
						_event
					)
				},
				sge::input::key::pressed{
					false
				}
			)
		);
}

awl::event::base_unique_ptr
sge::x11input::focus::object::on_focus_in()
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

	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::focus::event::in
			>(
				sge::input::focus::shared_ptr{
					this->fcppt_shared_from_this()
				}
			)
		);
}

awl::event::base_unique_ptr
sge::x11input::focus::object::on_focus_out()
{
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

	return
		fcppt::unique_ptr_to_base<
			awl::event::base
		>(
			fcppt::make_unique_ptr<
				sge::input::focus::event::out
			>(
				sge::input::focus::shared_ptr{
					this->fcppt_shared_from_this()
				}
			)
		);
}

awl::event::base_unique_ptr
sge::x11input::focus::object::process_key_down(
	sge::x11input::key::repeated const _repeated,
	sge::input::key::code const _key_code
)
{
	sge::input::focus::key const key(
		_key_code
	);

	return
		_repeated.get()
		?
			fcppt::unique_ptr_to_base<
				awl::event::base
			>(
				fcppt::make_unique_ptr<
					sge::input::focus::event::key_repeat
				>(
					sge::input::focus::shared_ptr{
						this->fcppt_shared_from_this()
					},
					key
				)
			)
		:
			fcppt::unique_ptr_to_base<
				awl::event::base
			>(
				fcppt::make_unique_ptr<
					sge::input::focus::event::key
				>(
					sge::input::focus::shared_ptr{
						this->fcppt_shared_from_this()
					},
					key,
					sge::input::key::pressed{
						true
					}
				)
			)
		;
}
