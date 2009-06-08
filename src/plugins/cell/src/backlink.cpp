/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../backlink.hpp"
#include "../grid_entry.hpp"

sge::cell::backlink::backlink(
	grid_entry &entry_,
	cell::circle &circle_)
:
	entry_(&entry_),
	circle_(&circle_)
{}

sge::cell::backlink::backlink(
	backlink const &l)
:
	entry_(l.entry_),
	circle_(l.circle_)
{
	add_me();
}

sge::cell::backlink &
sge::cell::backlink::operator=(
	backlink const &l)
{
	if(&l == this)
		return *this;
	unlink();
	entry_ = l.entry_;
	circle_ = l.circle_;
	add_me();
	return *this;
}

sge::cell::grid_entry &
sge::cell::backlink::entry()
{
	return *entry_;
}

sge::cell::circle &
sge::cell::backlink::circle()
{
	return *circle_;
}

void
sge::cell::backlink::add_me()
{
	entry().entries().push_back(
		*this
	);
}
