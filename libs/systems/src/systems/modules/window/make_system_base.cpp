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


#include <sge/src/systems/modules/window/make_system_base.hpp>
#include <sge/src/systems/modules/window/original_system.hpp>
#include <sge/src/systems/modules/window/system_base.hpp>
#include <sge/src/systems/modules/window/system_base_unique_ptr.hpp>
#include <sge/src/systems/modules/window/wrapped_system.hpp>
#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/variant/match.hpp>


sge::systems::modules::window::system_base_unique_ptr
sge::systems::modules::window::make_system_base(
	fcppt::log::context &_log_context,
	sge::systems::window const &_parameters
)
{
	return
		fcppt::variant::match(
			_parameters.source(),
			[
				&_log_context
			](
				sge::systems::original_window const &
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::systems::modules::window::system_base
					>(
						fcppt::make_unique_ptr<
							sge::systems::modules::window::original_system
						>(
							_log_context
						)
					);
			},
			[](
				sge::systems::wrapped_window const &_wrapped
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sge::systems::modules::window::system_base
					>(
						fcppt::make_unique_ptr<
							sge::systems::modules::window::wrapped_system
						>(
							_wrapped
						)
					);
			}
		);
}
