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


#include <sge/systems/window.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/make_base.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <sge/systems/impl/window/quit.hpp>
#include <sge/systems/impl/window/system.hpp>
#include <sge/window/object.hpp>
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
			_window_system.get(),
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
					_window_system.get(),
					base_->get()
				)
			)
		:
			optional_quit_unique_ptr()
	)
{
}

sge::systems::impl::window::object::~object()
{
}

sge::window::object &
sge::systems::impl::window::object::get() const
{
	return
		base_->get();
}

void
sge::systems::impl::window::object::post_init()
{
	if(
		show_on_post_
	)
		this->get().show();
}
