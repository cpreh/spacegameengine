/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/scenic/scene/entity.hpp>


sge::scenic::scene::entity::entity(
	sge::scenic::scene::mesh_path const &_mesh_path,
	sge::scenic::scene::position const &_position,
	sge::scenic::scene::rotation const &_rotation,
	sge::scenic::scene::scale const &_scale)
:
	mesh_path_(
		_mesh_path),
	position_(
		_position),
	rotation_(
		_rotation),
	scale_(
		_scale)
{
}

sge::scenic::scene::entity::entity(
	entity &&
) = default;

sge::scenic::scene::entity &
sge::scenic::scene::entity::operator=(
	entity &&
) = default;

sge::scenic::scene::mesh_path const &
sge::scenic::scene::entity::mesh_path() const
{
	return
		mesh_path_;
}

sge::scenic::scene::position const &
sge::scenic::scene::entity::position() const
{
	return
		position_;
}

sge::scenic::scene::rotation const &
sge::scenic::scene::entity::rotation() const
{
	return
		rotation_;
}

sge::scenic::scene::scale const &
sge::scenic::scene::entity::scale() const
{
	return
		scale_;
}

sge::scenic::scene::entity::~entity()
{
}
