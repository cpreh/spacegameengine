/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MD3_MODEL_HPP_INCLUDED
#define SGE_MD3_MODEL_HPP_INCLUDED

#include <istream>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/array.hpp>
#include "../math/vector.hpp"
#include "../renderer/types.hpp"

namespace sge
{

class md3_model {
public:
	md3_model(std::istream& data);
	
	typedef boost::int16_t s16;
	typedef boost::int32_t s32;
	typedef boost::uint8_t u8;
	typedef float f32;
	typedef std::basic_string<u8> string_type;
	typedef math::vector3 vec3;

	struct frame {
		frame(std::istream& is);
		
		vec3 min_bounds,
		     max_bounds,
		     local_origin;
		f32  radius;
		string_type name;
	};

	struct tag {
		tag(std::istream& is);
		
		string_type name;
		vec3 origin;
		boost::array<vec3, 3> axis;
	};

	struct surface {
		surface(std::istream& is, s32 num_frames);

		struct shader {
			shader(std::istream& is);

			string_type name;
			s32 shader_index;
		};

		struct triangle {
			triangle(std::istream& is);

			boost::array<s32, 3> indices;
		};

		struct texcoord {
			texcoord(std::istream& is);
			
			tex_pos tex;
		};

		struct vertex {
			vertex(std::istream& is);

			s16 x,
			    y,
			    z,
			    normal;
		};

		struct transformed_vertex {
			transformed_vertex(const vertex&);

			vec3 pos,
			     normal;
		};

		string_type name;

		typedef std::vector<shader>   shader_vector;
		shader_vector                 shaders;
		
		typedef std::vector<triangle> triangle_vector;
		triangle_vector               triangles;

		typedef std::vector<texcoord> texcoord_vector;
		texcoord_vector               st;

		typedef std::vector<transformed_vertex> transformed_vertex_vector;
		transformed_vertex_vector               transformed_vertices;
	};

private:
	static bool read_and_check_id3p(std::istream&);

	static vec3 read_vec3(std::istream&);

	template<std::size_t Max>
		static string_type read_string(std::istream&);

	static vec3 convert_normal(s16);

	string_type name_;

public: // TMP HACK
	typedef std::vector<frame>   frames_vector;
	frames_vector                frames;

	typedef std::vector<tag>     tags_vector;
	tags_vector                  tags;

	typedef std::vector<surface> surface_vector;
	surface_vector               surfaces;
};

}

#endif
