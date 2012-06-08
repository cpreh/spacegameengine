/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/plugin/traits.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/input/multi_processor.hpp>
#include <sge/src/input/multi_system.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>


sge::input::multi_system::multi_system(
	sge::input::plugin::collection const &_collection
)
:
	sge::input::system(),
	plugins_(),
	systems_()
{
	typedef sge::plugin::iterator<
		sge::input::system
	> plugin_iterator;

	for(
		plugin_iterator it(
			_collection.begin()
		);
		it
		!=
		_collection.end();
		++it
	)
	{
		fcppt::container::ptr::push_back_unique_ptr(
			plugins_,
			it->load()
		);

		fcppt::container::ptr::push_back_unique_ptr(
			systems_,
			plugins_.back().get()()
		);
	}
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
				fcppt::cref(
					_window
				),
				fcppt::cref(
					_window_system
				),
				fcppt::ref(
					systems_
				)
			)
		);
}
