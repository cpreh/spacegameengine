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


#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/impl/log_name.hpp>
#include <sge/input/impl/multi_processor.hpp>
#include <sge/input/impl/multi_system.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/plugin/context_fwd.hpp>
#include <sge/input/plugin/object.hpp>
#include <sge/input/plugin/traits.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::input::impl::multi_system::multi_system(
	fcppt::log::context &_log_context,
	sge::input::plugin::collection const &_collection
)
:
	sge::input::system(),
	log_{
		_log_context,
		sge::log::location(),
		sge::log::default_parameters(
			sge::input::impl::log_name()
		)
	},
	plugins_(
		fcppt::algorithm::map<
			sge::input::impl::multi_system::plugin_vector
		>(
			_collection,
			[](
				sge::input::plugin::context const &_context
			)
			{
				return
					_context.load();
			}
		)
	),
	systems_(
		fcppt::algorithm::map<
			sge::input::impl::system_ptr_vector
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

sge::input::impl::multi_system::~multi_system()
{
}

sge::input::processor_unique_ptr
sge::input::impl::multi_system::create_processor(
	sge::window::object const &_window,
	sge::window::system const &_window_system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::processor
		>(
			fcppt::make_unique_ptr<
				sge::input::impl::multi_processor
			>(
				log_,
				_window,
				_window_system,
				systems_
			)
		);
}

sge::input::capabilities_field
sge::input::impl::multi_system::capabilities() const
{
	return
		capabilities_;
}
