/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_MODEL_OBJ_PROTOTYPE_HPP_INCLUDED
#define SGE_MODEL_OBJ_PROTOTYPE_HPP_INCLUDED

#include <sge/model/obj/box.hpp>
#include <sge/model/obj/face_vertex_sequence.hpp>
#include <sge/model/obj/material_to_face_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/texture_coordinate_sequence.hpp>
#include <sge/model/obj/vertex_coordinate_sequence.hpp>
#include <sge/model/obj/material/file_sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class prototype
{
FCPPT_NONCOPYABLE(
	prototype);
public:
	SGE_MODEL_OBJ_SYMBOL
	explicit
	prototype(
		boost::filesystem::path const &
	);

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::vertex_coordinate_sequence const &
	vertex_coordinates() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::texture_coordinate_sequence const &
	texture_coordinates() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::normal_sequence const &
	normals() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::face_vertex_sequence const &
	face_vertices() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material_to_face_sequence const &
	parts() const;

	SGE_MODEL_OBJ_SYMBOL
	std::size_t
	face_count() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material::file_sequence const &
	material_files() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::box const &
	bounding_box() const;

	SGE_MODEL_OBJ_SYMBOL
	~prototype();
private:
	sge::model::obj::vertex_coordinate_sequence vertex_coordinates_;
	sge::model::obj::texture_coordinate_sequence texture_coordinates_;
	sge::model::obj::normal_sequence normals_;
	sge::model::obj::face_vertex_sequence face_vertices_;
	sge::model::obj::material_to_face_sequence parts_;
	sge::model::obj::material::file_sequence material_files_;
	sge::model::obj::box bounding_box_;
};
}
}
}

#endif
