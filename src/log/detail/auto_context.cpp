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


#include <sge/log/detail/auto_context.hpp>
#include <sge/log/context.hpp>
#include <sge/optional_impl.hpp>
#include <sge/assert.hpp>

sge::log::detail::auto_context::auto_context(
	context *const context_,
	object &object_,
	optional_location const &location_
)
:
	context_(context_),
	object_(object_),
	location_(location_)
{
	if(context_)
	{
		SGE_ASSERT(location_);

		context_->add(
			*location_,
			object_
		);
	}
}

sge::log::detail::auto_context::~auto_context()
{
	if(context_)
		context_->remove(
			*location_,
			object_
		);
}

sge::log::optional_location const
sge::log::detail::auto_context::location() const
{
	return location_;
}
