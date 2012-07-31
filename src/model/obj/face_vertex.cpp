#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/face_vertex.hpp>

sge::model::obj::face_vertex::face_vertex(
	sge::model::obj::vertex_coordinate_index const &_vertex_coordinate_index,
	sge::model::obj::texture_coordinate_index const &_texture_coordinate_index,
	sge::model::obj::normal_index const &_normal_index)
:
	indices_()
{
	indices_[0] =
		_vertex_coordinate_index.get();
	indices_[1] =
		_texture_coordinate_index.get();
	indices_[2] =
		_normal_index.get();
}

sge::model::obj::vertex_coordinate_index const
sge::model::obj::face_vertex::vertex_coordinate_index() const
{
	return
		sge::model::obj::vertex_coordinate_index(
			indices_[0u]);
}

sge::model::obj::texture_coordinate_index const
sge::model::obj::face_vertex::texture_coordinate_index() const
{
	return
		sge::model::obj::texture_coordinate_index(
			indices_[1u]);
}

sge::model::obj::normal_index const
sge::model::obj::face_vertex::normal_index() const
{
	return
		sge::model::obj::normal_index(
			indices_[2u]);
}

/*
bool
sge::model::obj::face_vertex::operator==(
	face_vertex const &_other) const
{
	return
		vertex_coordinate_index_ == _other.vertex_coordinate_index_ &&
		texture_coordinate_index_ == _other.texture_coordinate_index_ &&
		normal_index_ == _other.normal_index_;
}
*/
