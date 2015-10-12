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
