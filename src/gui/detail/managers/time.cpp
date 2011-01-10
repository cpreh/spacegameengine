/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/detail/managers/time.hpp>
#include <sge/gui/timer/object.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::gui::timer::object_ptr const
sge::gui::detail::managers::time::add(
	sge::time::duration const &r,
	timer::callback const cb
)
{
	timer::object_ptr const p(
		fcppt::make_shared_ptr<
			timer::object
		>(
			r,
			cb
		)
	);

	timers.push_back(p);

	return p;
}

void sge::gui::detail::managers::time::update()
{
	for (timer_container::iterator i = timers.begin(); i != timers.end();)
	{
		if ((*i).expired())
		{
			i = timers.erase(i);
			continue;
		}
		(*i).lock()->update();
		++i;
	}
}
