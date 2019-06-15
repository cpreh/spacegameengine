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


#include <sge/systems/original_window.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/renderer/system.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/original.hpp>
#include <sge/systems/impl/window/to_awl_parameters.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/cursor/const_optional_object_ref.hpp>
#include <awl/cursor/object.hpp>
#include <awl/cursor/optional_type.hpp>
#include <awl/cursor/type.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <awl/visual/object.hpp>
#include <awl/window/object.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>


sge::systems::impl::window::original::original(
	sge::systems::original_window const &_parameters,
	sge::window::system &_system,
	sge::systems::impl::renderer::optional_system_ref const &_opt_renderer_system
)
:
	sge::systems::impl::window::base(),
	awl_visual_(
		fcppt::optional::maybe(
			_opt_renderer_system,
			[
				&_system
			]{
				return
					_system.awl_system().default_visual();
			},
			[](
				fcppt::reference<
					sge::systems::impl::renderer::system
				> const _renderer_system
			)
			{
				return
					_renderer_system.get().create_visual();
			}
		)
	),
	awl_cursor_(
		_system.awl_system().create_cursor(
			_parameters.hide_cursor()
			?
				awl::cursor::optional_type{}
			:
				awl::cursor::optional_type{
					awl::cursor::type::arrow
				}
		)
	),
	awl_window_(
		_system.awl_system().create_window(
			sge::systems::impl::window::to_awl_parameters(
				*awl_visual_,
				awl::cursor::const_optional_object_ref(
					fcppt::make_cref(
						*awl_cursor_
					)
				),
				_parameters
			)
		)
	),
	window_(
		_system,
		*awl_window_
	)
{
}

sge::systems::impl::window::original::~original()
{
}

sge::window::object &
sge::systems::impl::window::original::get() const
{
	return
		window_;
}
