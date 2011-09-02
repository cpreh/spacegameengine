/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MODEL_MD3_SURFACE_HPP_INCLUDED
#define SGE_MODEL_MD3_SURFACE_HPP_INCLUDED

#include "s32.hpp"
#include "shader_vector.hpp"
#include "texpos_vector.hpp"
#include "transformed_vertex_vector.hpp"
#include "triangle_vector.hpp"
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/string.hpp>
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
		md3::load_flags::type,
		md3::s32 num_frames
	);

	md3::string const &
	name() const;

	md3::shader_vector const &
	shaders() const;

	md3::triangle_vector const &
	triangles() const;

	md3::texpos_vector const &
	texpos() const;

	md3::transformed_vertex_vector const &
	transformed_vertices() const;
private:
	md3::string name_;

	md3::shader_vector shaders_;

	md3::triangle_vector triangles_;

	md3::texpos_vector texpos_;

	md3::transformed_vertex_vector transformed_vertices_;
};

}
}
}

#endif
