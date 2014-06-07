/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/rucksack/testbed/object.hpp>
#include <sge/rucksack/testbed/systems_fwd.hpp>
#include <sge/src/rucksack/testbed/object_impl.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::rucksack::testbed::object::object(
	sge::window::title const &_str)
:
	impl_(
		fcppt::make_unique_ptr<
			sge::rucksack::testbed::object_impl>(
			_str))
{
}

void
sge::rucksack::testbed::object::add_widget(
	sge::rucksack::widget::base &_widget,
	sge::image::color::any::object const &_color)
{
	return
		impl_->add_widget(
			_widget,
			_color);
}

awl::main::exit_code const
sge::rucksack::testbed::object::run()
{
	return
		impl_->run();
}

sge::rucksack::testbed::systems const &
sge::rucksack::testbed::object::systems() const
{
	return
		impl_->systems();
}

sge::rucksack::testbed::object::~object()
{
}
