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


#ifndef SGE_SRC_MODEL_MD3_SURFACE_HPP_INCLUDED
#define SGE_SRC_MODEL_MD3_SURFACE_HPP_INCLUDED

#include <sge/model/md3/load_flags_field_fwd.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/src/model/md3/s32.hpp>
#include <sge/src/model/md3/shader_vector.hpp>
#include <sge/src/model/md3/texpos_vector.hpp>
#include <sge/src/model/md3/transformed_vertex_vector.hpp>
#include <sge/src/model/md3/triangle_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{

class surface
{
public:
	surface(
		std::istream &,
		sge::model::md3::load_flags_field,
		sge::model::md3::s32 num_frames
	);

	sge::model::md3::string const &
	name() const;

	sge::model::md3::shader_vector const &
	shaders() const;

	sge::model::md3::triangle_vector const &
	triangles() const;

	sge::model::md3::texpos_vector const &
	texpos() const;

	sge::model::md3::transformed_vertex_vector const &
	transformed_vertices() const;
private:
	sge::model::md3::string name_;

	sge::model::md3::shader_vector shaders_;

	sge::model::md3::triangle_vector triangles_;

	sge::model::md3::texpos_vector texpos_;

	sge::model::md3::transformed_vertex_vector transformed_vertices_;
};

}
}
}

#endif
