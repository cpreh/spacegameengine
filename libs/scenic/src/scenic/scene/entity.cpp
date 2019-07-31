//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
