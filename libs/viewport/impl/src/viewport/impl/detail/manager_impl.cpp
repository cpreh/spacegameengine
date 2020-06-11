//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/viewport/resize_callback.hpp>
#include <sge/viewport/impl/detail/manager_impl.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::viewport::detail::manager_impl::manager_impl(
	sge::renderer::device::core_ref const _device,
	sge::window::object_ref const _window,
	sge::viewport::optional_resize_callback &&_resize_callback
)
:
	target_{
		_device.get().onscreen_target()
	},
	resize_callback_{
		std::move(
			_resize_callback
		)
	},
	event_connection_{
		_window.get().event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_resize(
							_event
						);
				}
			}
		)
	},
	manage_signal_()
{
}
FCPPT_PP_POP_WARNING

sge::viewport::detail::manager_impl::~manager_impl()
= default;

fcppt::signal::auto_connection
sge::viewport::detail::manager_impl::manage_callback(
	sge::viewport::manage_callback &&_callback
)
{
	return
		manage_signal_.connect(
			std::move(
				_callback
			)
		);
}

void
sge::viewport::detail::manager_impl::resize_callback(
	sge::viewport::optional_resize_callback &&_resize_callback
)
{
	resize_callback_ =
		std::move(
			_resize_callback
		);
}

sge::renderer::target::viewport
sge::viewport::detail::manager_impl::viewport() const
{
	return
		target_.viewport();
}

awl::event::container
sge::viewport::detail::manager_impl::on_resize(
	awl::window::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::window::event::resize const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				awl::window::event::resize const
			> const _resize
		)
		{
			// TODO(philipp): Turn this into events that we can return.
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
							_resize.get()
						)
					);
				}
			);

			manage_signal_(
				this->viewport()
			);
		}
	);

	return
		awl::event::container();
}
