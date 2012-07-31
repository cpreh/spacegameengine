#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/face_vertex.hpp>

sge::model::obj::face_vertex::face_vertex(
	sge::model::obj::vertex_coordinate_index const &_vertex_coordinate_index,
	sge::model::obj::texture_coordinate_index const &_texture_coordinate_index,
	sge::model::obj::normal_index const &_normal_index)
:
	vertex_coordinate_index_(
		_vertex_coordinate_index),
	texture_coordinate_index_(
		_texture_coordinate_index),
	normal_index_(
		_normal_index)
{
}

sge::model::obj::vertex_coordinate_index const &
sge::model::obj::face_vertex::vertex_coordinate_index() const
{
	return
		vertex_coordinate_index_;
}

sge::model::obj::texture_coordinate_index const &
sge::model::obj::face_vertex::texture_coordinate_index() const
{
	return
		texture_coordinate_index_;
}

sge::model::obj::normal_index const &
sge::model::obj::face_vertex::normal_index() const
{
	return
		normal_index_;
}

bool
sge::model::obj::face_vertex::operator==(
	face_vertex const &_other) const
{
	return
		vertex_coordinate_index_ == _other.vertex_coordinate_index_ &&
		texture_coordinate_index_ == _other.texture_coordinate_index_ &&
		normal_index_ == _other.normal_index_;
}
