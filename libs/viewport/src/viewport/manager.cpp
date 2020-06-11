//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/optional_resize_callback_fwd.hpp>
#include <sge/viewport/impl/detail/manager_impl.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::viewport::manager::manager(
	sge::renderer::device::core_ref const _device,
	sge::window::object_ref const _window,
	sge::viewport::optional_resize_callback &&_resize_callback
)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::viewport::detail::manager_impl
		>(
			_device,
			_window,
			std::move(
				_resize_callback
			)
		)
	)
{
}

sge::viewport::manager::~manager()
= default;

fcppt::signal::auto_connection
sge::viewport::manager::manage_callback(
	sge::viewport::manage_callback &&_callback
)
{
	return
		impl_->manage_callback(
			std::move(
				_callback
			)
		);
}

void
sge::viewport::manager::resize_callback(
	sge::viewport::optional_resize_callback &&_resize_callback
)
{
	impl_->resize_callback(
		std::move(
			_resize_callback
		)
	);
}

sge::renderer::target::viewport
sge::viewport::manager::viewport() const
{
	return
		impl_->viewport();
}
