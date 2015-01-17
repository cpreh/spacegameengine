/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/plugin/context_fwd.hpp>
#include <sge/input/plugin/object.hpp>
#include <sge/input/plugin/traits.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/load_with_log_options.hpp>
#include <sge/src/input/multi_processor.hpp>
#include <sge/src/input/multi_system.hpp>
#include <sge/src/input/system_ptr_vector.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>


sge::input::multi_system::multi_system(
	sge::input::plugin::collection const &_collection,
	sge::log::option_container const &_log_options
)
:
	sge::input::system(),
	plugins_(
		fcppt::algorithm::map<
			sge::input::multi_system::plugin_vector
		>(
			_collection,
			[
				&_log_options
			](
				sge::input::plugin::context const &_context
			)
			{
				return
					sge::plugin::load_with_log_options(
						_context,
						_log_options
					);
			}
		)
	),
	systems_(
		fcppt::algorithm::map<
			sge::input::system_ptr_vector
		>(
			plugins_,
			[](
				sge::input::plugin::object const &_plugin
			)
			{
				return
					_plugin.get()();
			}
		)
	),
	capabilities_(
		fcppt::algorithm::fold(
			systems_,
			sge::input::capabilities_field::null(),
			[](
				sge::input::system_unique_ptr const &_system,
				sge::input::capabilities_field const &_state
			)
			{
				return
					_state
					|
					_system->capabilities();
			}
		)
	)
{
}

sge::input::multi_system::~multi_system()
{
}

sge::input::processor_unique_ptr
sge::input::multi_system::create_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
{
	return
		sge::input::processor_unique_ptr(
			fcppt::make_unique_ptr<
				sge::input::multi_processor
			>(
				_window,
				_window_system,
				systems_
			)
		);
}

sge::input::capabilities_field const
sge::input::multi_system::capabilities() const
{
	return
		capabilities_;
}
