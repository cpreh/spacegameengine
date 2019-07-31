//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/model/obj/face_vertex.hpp>
#include <sge/model/obj/normal_index.hpp>
#include <sge/model/obj/texture_coordinate_index.hpp>
#include <sge/model/obj/vertex_coordinate_index.hpp>


sge::model::obj::face_vertex::face_vertex(
	sge::model::obj::vertex_coordinate_index const &_vertex_coordinate_index,
	sge::model::obj::texture_coordinate_index const &_texture_coordinate_index,
	sge::model::obj::normal_index const &_normal_index)
:
	indices_{{
		_vertex_coordinate_index.get(),
		_texture_coordinate_index.get(),
		_normal_index.get()
	}}
{
}

sge::model::obj::vertex_coordinate_index
sge::model::obj::face_vertex::vertex_coordinate_index() const
{
	return
		sge::model::obj::vertex_coordinate_index(
			indices_[0u]);
}

sge::model::obj::texture_coordinate_index
sge::model::obj::face_vertex::texture_coordinate_index() const
{
	return
		sge::model::obj::texture_coordinate_index(
			indices_[1u]);
}

sge::model::obj::normal_index
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
