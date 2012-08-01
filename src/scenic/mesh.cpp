#include <sge/scenic/mesh.hpp>

sge::scenic::mesh::mesh(
	sge::model::obj::instance &_model,
	sge::scenic::position const &_position,
	sge::scenic::rotation const &_rotation,
	sge::scenic::scale const &_scale)
:
	model_(
		_model)
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
