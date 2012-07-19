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


#include <sge/model/manager/instance/object.hpp>
#include <sge/model/manager/object.hpp>

sge::model::manager::instance::object::object(
	sge::model::manager::object &_manager,
	sge::model::manager::instance::identifier const &_identifier,
	sge::model::manager::instance::position const &_position)
:
	identifier_(
		_identifier),
	position_(
		_position)
{
	_manager.add_instance(
		*this);
}

sge::model::manager::instance::identifier const &
sge::model::manager::instance::object::identifier() const
{
	return
		identifier_;
}

sge::model::manager::instance::position const &
sge::model::manager::instance::object::position() const
{
	return
		position_;
}

sge::model::manager::instance::object::~object()
{
}
