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


#include <sge/x11input/atom_name.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/free.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::atom_name::atom_name(
	awl::backends::x11::display &_display,
	Atom const _atom
)
:
	name_(
		::XGetAtomName(
			_display.get(),
			_atom
		)
	)
{
}

sge::x11input::atom_name::~atom_name()
{
	awl::backends::x11::free(
		name_
	);
}

char const *
sge::x11input::atom_name::get() const
{
	return name_;
}
