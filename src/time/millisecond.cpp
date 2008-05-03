/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/time/millisecond.hpp>
#include <sge/time/time.hpp>

sge::time::millisecond::millisecond(
	const space_unit tm)
: resolution(
	static_cast<unit>(
		tm * static_cast<space_unit>(
			hz()) * static_cast<space_unit>(1000)))
{}

sge::time::millisecond::millisecond(
	const unit tm)
: resolution(
	tm * hz() / 1000)
{}
