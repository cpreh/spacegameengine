/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MD3_OBJECT_HPP_INCLUDED
#define SGE_MD3_OBJECT_HPP_INCLUDED

#include <sge/model/object.hpp>
#include <sge/model/istream.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/typeswitch.hpp>
#include <boost/tr1/array.hpp>
#include <vector>
#include <string>

namespace sge
{
namespace md3
{

class object : public model::object {
public:
	explicit object(
		model::istream &);

	renderer::vf::dynamic_format const
	format() const;

	renderer::size_type
	vertices() const;

	renderer::size_type
	indices() const;

	void
	copy_vertices(
		renderer::vf::dynamic_view const &);
	
	void
	copy_indices(
		renderer::index::view const &);
private:
	// TODO: split this!
	typedef int16 s16;
	typedef int32 s32;
	typedef uint8 u8;
	typedef float f32;
	typedef std::basic_string<u8> string;
	typedef math::vector::static_<
		f32,
		3
	>::type vec3;

	struct frame {
		frame(std::istream& is);
		
		vec3 min_bounds,
		     max_bounds,
		     local_origin;
		f32  radius;
		string name;
	};

	struct tag {
		explicit tag(model::istream& is);
		
		string                           name;
		vec3                             origin;
		typedef std::tr1::array<vec3, 3> axis_array;
		axis_array                       axis;
	};

	struct surface {
		surface(std::istream& is, s32 num_frames);

		struct shader {
			explicit shader(model::istream &);

			string name;
			s32 shader_index;
		};

		struct triangle {
			explicit triangle(model::istream &);
			typedef std::tr1::array<s32, 3> index_array;
			index_array indices;
		};

		struct texcoord {
			explicit texcoord(model::istream &);
			
			typedef math::vector::static_<
				f32,
				2
			>::type tex_pos;

			tex_pos tex;
		};

		struct vertex {
			explicit vertex(model::istream &);

			s16 x,
			    y,
			    z,
			    normal;
		};

		struct transformed_vertex {
			explicit transformed_vertex(vertex const &);

			vec3 pos,
			     normal;
		};

		string name;

		typedef std::vector<shader>   shader_vector;
		shader_vector                 shaders;
		
		typedef std::vector<triangle> triangle_vector;
		triangle_vector               triangles;

		typedef std::vector<texcoord> texcoord_vector;
		texcoord_vector               st;

		typedef std::vector<transformed_vertex> transformed_vertex_vector;
		transformed_vertex_vector               transformed_vertices;
	};

	static bool read_and_check_id3p(model::istream &);

	static vec3 read_vec3(std::istream&);

	template<
		string::size_type Max
	>
	static string const read_string(model::istream &);

	static vec3 convert_normal(s16);

	renderer::size_type indices_;
	renderer::size_type vertices_;

	string name_;

	typedef std::vector<frame>   frames_vector;
	frames_vector                frames;

	typedef std::vector<tag>     tags_vector;
	tags_vector                  tags;

	typedef std::vector<surface> surface_vector;
	surface_vector               surfaces;
};

}
}

#endif
