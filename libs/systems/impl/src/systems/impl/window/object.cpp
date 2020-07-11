//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/window.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/make_base.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <sge/systems/impl/window/quit.hpp>
#include <sge/systems/impl/window/system.hpp>
#include <sge/window/object.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::systems::impl::window::object::object(
	sge::systems::window const &_parameters,
	sge::systems::impl::window::system const &_window_system,
	sge::systems::impl::renderer::optional_system_ref const &_renderer_system
)
:
	base_(
		sge::systems::impl::window::make_base(
			_parameters,
			fcppt::make_ref(
				_window_system.get()
			),
			_renderer_system
		)
	),
	show_on_post_(
		_parameters.show()
	),
	quit_(
		_parameters.quit()
		?
			optional_quit_unique_ptr(
				fcppt::make_unique_ptr<
					sge::systems::impl::window::quit
				>(
					fcppt::make_ref(
						_window_system.get()
					),
					fcppt::make_ref(
						base_->get()
					)
				)
			)
		:
			optional_quit_unique_ptr()
	)
{
}

sge::systems::impl::window::object::~object()
= default;

sge::window::object &
sge::systems::impl::window::object::get() const
{
	return
		base_->get();
}

void
sge::systems::impl::window::object::post_init() const
{
	if(
		show_on_post_
	)
	{
		this->get().show();
	}
}
