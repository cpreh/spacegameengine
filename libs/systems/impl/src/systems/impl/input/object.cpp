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


#include <sge/input/capabilities.hpp>
#include <sge/input/capabilities_field.hpp>
#include <sge/input/capabilities_to_string.hpp>
#include <sge/input/create_multi_system.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/system.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/impl/input/cursor_modifier.hpp>
#include <sge/systems/impl/input/cursor_modifier_unique_ptr.hpp>
#include <sge/systems/impl/input/object.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/comparison.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::systems::impl::input::object::object(
	fcppt::log::context &_log_context,
	fcppt::log::object &_log,
	sge::input::plugin::collection const &_collection,
	sge::systems::input const &_parameters,
	sge::systems::impl::window::object const &_window_object
)
:
	input_system_{
		sge::input::create_multi_system(
			_log_context,
			_collection
		)
	},
	input_processor_{
		input_system_->create_processor(
			_window_object.get()
		)
	},
	cursor_modifier_{
		fcppt::optional::make_if(
			_parameters.cursor_options()
			!=
			sge::systems::cursor_option_field::null(),
			[
				&_window_object,
				&_parameters,
				this
			]{
				return
					fcppt::make_unique_ptr<
						sge::systems::impl::input::cursor_modifier
					>(
						*this->input_processor_,
						_window_object.get(),
						_parameters.cursor_options()
					);
			}
		)
	}
{
	for(
		sge::input::capabilities const element
		:
		{
			sge::input::capabilities::cursor,
			sge::input::capabilities::keyboard,
			sge::input::capabilities::mouse
		}
	)
		if(
			!(
				input_system_->capabilities()
				&
				element
			)
		)
		{
			FCPPT_LOG_WARNING(
				_log,
				fcppt::log::out
					<<
					FCPPT_TEXT("None of your input plugins handles capability ")
					<<
					sge::input::capabilities_to_string(
						element
					)
			);
		}
}

sge::systems::impl::input::object::~object()
{
}

sge::input::system &
sge::systems::impl::input::object::system() const
{
	return
		*input_system_;
}

sge::input::processor &
sge::systems::impl::input::object::processor() const
{
	return
		*input_processor_;
}
