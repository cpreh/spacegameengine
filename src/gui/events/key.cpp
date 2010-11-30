/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/gui/events/key.hpp>
#include <fcppt/container/map_impl.hpp>

sge::gui::events::key::key(
	input::keyboard::key_event const &_value,
	input::modifier::states const &_modifiers,
	bool const _repeated
)
:
	value_(_value),
	modifiers_(_modifiers),
	repeated_(_repeated)
{
}

sge::input::keyboard::key_event const &
sge::gui::events::key::value() const
{
	return value_;
}

sge::input::modifier::states const &
sge::gui::events::key::modifiers() const
{
	return modifiers_;
}

bool
sge::gui::events::key::repeated() const
{
	return repeated_;
}
