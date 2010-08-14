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


#include <sge/xcb/window/attribute/list.hpp>
#include <sge/xcb/window/attribute/enum_to_mask.hpp>
#include <sge/xcb/window/attribute/enum_to_mask.hpp>
#include <fcppt/container/raw_vector_impl.hpp>

sge::xcb::window::attribute::list::list()
:
	container_(),
	mask_(0)
{}

sge::xcb::window::attribute::list::list(
	size_type const size_
)
:
	container_(),
	mask_(0)
{
	container_.reserve(
		size_
	);
}

sge::xcb::window::attribute::list::~list()
{}

void
sge::xcb::window::attribute::list::add(
	enum_::type const what_,
	value const &value_
)
{
	mask_ |=
		enum_to_mask(
			what_
		);

	container_.push_back(
		value_
	);
}

sge::xcb::window::attribute::value const *
sge::xcb::window::attribute::list::data() const
{
	return container_.data();
}

sge::xcb::value_mask const
sge::xcb::window::attribute::list::value_mask() const
{
	return mask_;
}
