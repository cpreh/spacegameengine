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


#include <sge/console/var_base.hpp>
#include <sge/console/object.hpp>

sge::console::var_base::var_base(
	object &_object,
	fcppt::string const &_name
)
:
	object_(_object),
	name_(_name)
{
	object_.insert(*this);
}

fcppt::string const
sge::console::var_base::name() const
{
	return name_;
}

sge::console::var_base::~var_base()
{
	object_.erase(*this);
}
