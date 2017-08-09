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


#include <sge/systems/impl/window/quit.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/window/event/base.hpp>
#include <awl/window/event/close.hpp>
#include <awl/window/event/destroy.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::impl::window::quit::quit(
	sge::window::system &_system,
	sge::window::object &_window
)
:
	system_{
		_system
	},
	destroy_connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::variant::dynamic_cast_<
							boost::mpl::vector2<
								awl::window::event::destroy const,
								awl::window::event::close const
							>,
							fcppt::cast::dynamic_fun
						>(
							_event
						),
						[
							this
						](
							auto const &
						)
						{
							system_.quit(
								awl::main::exit_success()
							);
						}
					);

					return
						awl::event::container();
				}
			}
		)
	}
{
}
FCPPT_PP_POP_WARNING

sge::systems::impl::window::quit::~quit()
{
}
