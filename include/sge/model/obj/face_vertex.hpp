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


#ifndef SGE_MODEL_OBJ_FACE_VERTEX_HPP_INCLUDED
#define SGE_MODEL_OBJ_FACE_VERTEX_HPP_INCLUDED

#include <sge/model/obj/normal_index.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/texture_coordinate_index.hpp>
#include <sge/model/obj/vertex_coordinate_index.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class face_vertex
{
public:
	SGE_MODEL_OBJ_SYMBOL
	face_vertex(
		sge::model::obj::vertex_coordinate_index const &,
		sge::model::obj::texture_coordinate_index const &,
		sge::model::obj::normal_index const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::vertex_coordinate_index const &
	vertex_coordinate_index() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::texture_coordinate_index const &
	texture_coordinate_index() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::normal_index const &
	normal_index() const;

	/*
	bool
	operator<(
		face_vertex const &) const;
	*/

	SGE_MODEL_OBJ_SYMBOL
	bool
	operator==(
		face_vertex const &) const;
private:
	sge::model::obj::vertex_coordinate_index vertex_coordinate_index_;
	sge::model::obj::texture_coordinate_index texture_coordinate_index_;
	sge::model::obj::normal_index normal_index_;
};
}
}
}

#endif
