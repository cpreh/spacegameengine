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


#include <sge/log/context_location.hpp>
#include <sge/assert.hpp>

sge::log::context_location::context_location()
:
	context_(),
	location_()
{}

sge::log::context_location::context_location(
	log::context *const context_,
	log::location const &location_
)
:
	context_(context_),
	location_(location_)
{}

sge::log::context *
sge::log::context_location::context() const
{
	return context_;
}

sge::log::location const &
sge::log::context_location::location() const
{
	SGE_ASSERT(
		location_
	);

	return *location_;
}
