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


#ifndef SGE_MD3_OBJECT_IMPL_HPP_INCLUDED
#define SGE_MD3_OBJECT_IMPL_HPP_INCLUDED

#include <sge/md3/object.hpp>
#include <sge/md3/load_flags.hpp>
#include <sge/md3/scalar.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/container/array.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/cstdint.hpp>
#include <vector>
#include <string>
#include <cstddef>
#include <istream>

namespace sge
{
namespace md3
{

class object_impl
:
	public md3::object
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	object_impl(
		std::istream &,
		md3::load_flags::type
	);

	~object_impl();

	md3::index_sequence const
	indices(
		fcppt::string const &
	) const;

	md3::vertex_sequence const
	vertices(
		fcppt::string const &
	) const;

	fcppt::optional<md3::texcoord_sequence> const
	texcoords(
		fcppt::string const &
	) const;

	fcppt::optional<md3::normal_sequence> const
	normals(
		fcppt::string const &
	) const;

	md3::part_name_sequence const
	part_names() const;
private: // TODO!
	// TODO: split this!
	typedef boost::int16_t s16;
	typedef boost::int32_t s32;
	typedef boost::uint8_t u8;
	// FIXME: This isn't comparable, really
	//typedef std::basic_string<u8> string;
	typedef fcppt::string string;
	typedef fcppt::math::vector::static_<
		scalar,
		3
	>::type vec3;

	class frame {
	public:
		frame(std::istream& is);

		vec3 min_bounds,
		     max_bounds,
		     local_origin;
		scalar  radius;
		string name;
	};

	class tag {
	public:
		explicit tag(std::istream& is);

		string name;
		vec3 origin;
		typedef fcppt::container::array<vec3, 3> axis_array;
		axis_array axis;
	};

	class surface {
	public:
		surface(std::istream& is, md3::load_flags::type, s32 num_frames);

		class shader {
		public:
			explicit shader(std::istream &);

			string name;
			s32 shader_index;
		};

		class triangle {
		public:
			explicit triangle(std::istream &);
			typedef fcppt::container::array<s32, 3> index_array;
			index_array indices;
		};

		class texcoord {
		public:
			explicit texcoord(std::istream &);

			typedef fcppt::math::vector::static_<
				scalar,
				2
			>::type tex_pos;

			tex_pos tex;
		};

		class vertex {
		public:
			explicit vertex(std::istream &,md3::load_flags::type);

			s16 x,
			    y,
			    z,
			    normal;
		};

		class transformed_vertex {
		public:
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

	static bool read_and_check_id3p(std::istream &);

	static vec3 read_vec3(std::istream&);

	template<
		string::size_type Max
	>
	static string const read_string(std::istream &);

	static vec3 convert_normal(s16);

	std::size_t
		vertices_,
		indices_;

	string name_;

	typedef std::vector<frame>   frames_vector;
	frames_vector                frames_;

	typedef std::vector<tag>     tags_vector;
	tags_vector                  tags_;

	typedef std::vector<surface> surface_vector;
	surface_vector               surfaces_;

	surface_vector::const_reference
	surface_by_name(
		fcppt::string const &
	) const;
};

}
}

#endif
