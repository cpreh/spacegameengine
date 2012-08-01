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


#include <sge/scenic/mesh.hpp>

sge::scenic::mesh::mesh(
	sge::model::obj::instance &_model,
	sge::scenic::position const &_position,
	sge::scenic::rotation const &_rotation,
	sge::scenic::scale const &_scale)
:
	model_(
		_model),
	position_(
		_position),
	rotation_(
		_rotation),
	scale_(
		_scale)
{
}

sge::model::obj::instance &
sge::scenic::mesh::model() const
{
	return
		model_;
}

sge::scenic::position const &
sge::scenic::mesh::position() const
{
	return
		position_;
}

sge::scenic::rotation const &
sge::scenic::mesh::rotation() const
{
	return
		rotation_;
}

sge::scenic::scale const &
sge::scenic::mesh::scale() const
{
	return
		scale_;
}

sge::scenic::mesh::~mesh()
{
}
