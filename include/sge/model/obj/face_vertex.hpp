/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/model/obj/texture_coordinate_index.hpp>
#include <sge/model/obj/vertex_coordinate_index.hpp>
#include <sge/model/obj/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/functional/hash.hpp>
#include <array>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class face_vertex
{
public:
	SGE_MODEL_OBJ_DETAIL_SYMBOL
	face_vertex(
		sge::model::obj::vertex_coordinate_index const &,
		sge::model::obj::texture_coordinate_index const &,
		sge::model::obj::normal_index const &);

	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::vertex_coordinate_index
	vertex_coordinate_index() const;

	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::texture_coordinate_index
	texture_coordinate_index() const;

	SGE_MODEL_OBJ_DETAIL_SYMBOL
	sge::model::obj::normal_index
	normal_index() const;

	bool
	operator==(
		face_vertex const &_other) const
	{
		return
			indices_ == _other.indices_;
	}

	bool
	operator<(
		face_vertex const &_other) const
	{
		return
			indices_ < _other.indices_;
	}

	friend std::size_t
	hash_value(
		face_vertex const &_vertex)
	{
		std::size_t seed = 0u;
		boost::hash_combine(
			seed,
			_vertex.indices_[0u]);
		boost::hash_combine(
			seed,
			_vertex.indices_[1u]);
		boost::hash_combine(
			seed,
			_vertex.indices_[2u]);
		return seed;
	}
private:
	typedef
	std::array<std::size_t,3>
	index_array;

	index_array indices_;
};
}
}
}

#endif
